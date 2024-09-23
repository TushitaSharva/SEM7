#include <iostream>
#include <vector>
#include <random>
#include <string.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <mutex>
#include <chrono>
#include <fstream>
#include <atomic>
#include <thread>
using ll = long long;


/* UTILITY FUNCTIONS SECTION STARTS HERE */
// Logger class, for printing and logging to log files and debugging
class Logger
{
public:
    template<typename... Args>
    void DEBUG(Args... args)
    {
        std::ofstream debugfile("outputs/debug.txt", std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Use fold expression to stream all arguments
        debugfile << oss.str() << "\n";
        debugfile.close();
    }

    template<typename... Args>
    void OUTPUT(Args... args)
    {
        std::ofstream outputfile("outputs/out_bakery.txt", std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Stream all arguments
        outputfile << oss.str() << "\n";
        outputfile.close();
    }
};

// Function to convert time_point to a formatted string
std::string getSysTime(const std::chrono::high_resolution_clock::time_point& tp)
{
    auto time_t = std::chrono::high_resolution_clock::to_time_t(tp);
    std::tm* tm = std::localtime(&time_t); // Convert to local time
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
    return std::string(buffer);
}

// Function to generates a random number from an exponential distribution with a mean of 'exp_time'.
double Timer(float lambda)
{
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::exponential_distribution<double> distr(1.0 / lambda);
    return distr(gen);
}

/* UTILITY FUNCTIONS SECTION ENDS HERE */


// Global variables required
static Logger LOGGER;
int n;
int k;
float l1;
float l2;

// Lock class
class Bakery
{
    std::atomic<bool> *flag;
    std::atomic<ll> *label;
    std::atomic<ll> maxLabel;

    bool compare(int i, int j)
    {
        ll label_i = label[i].load();
        ll label_j = label[j].load();

        if(label_i < label_j)
        {
            return true;
        }

        else if(label_i == label_j && i < j)
        {
            return true;
        }

        return false;
    }

public:
    Bakery(int n)
    {
        flag = new std::atomic<bool>[n];
        label = new std::atomic<ll>[n];

        for(int i = 0; i < n; i++)
        {
            flag[i].store(false);
            label[i].store(0);
        }

        maxLabel.store(0);
    }

    void lock(int threadId)
    {
        int i = threadId;
        flag[i].store(true);

        // Set the label for the current thread
        label[i].store(maxLabel.load() + 1);
        maxLabel.store(std::max(maxLabel.load(), label[i].load()));

        // Wait until it's safe to enter CS
        for (int j = 0; j < n; j++) {
            if (j != i) {
                while (flag[j].load() && compare(j, i)) {
                    // Busy wait
                }
            }
        }
    }

    void unlock(int threadId)
    {
        flag[threadId].store(false);
    }

    ~Bakery() {
        delete[] flag;
        delete[] label;
    }
};

class ThreadData
{
    int threadId;
    ll waitingTime;

public:
    ThreadData()
    {
        threadId = 0;
        waitingTime = 0;
    }

    int getThreadId()
    {
        return threadId;
    }

    void setThreadId(int tid)
    {
        this->threadId = tid;
    }

    void setWaitingTime(ll waitingTime)
    {
        this->waitingTime = waitingTime;
    }

    ll getWaitingTime()
    {
        return waitingTime;
    }

    void incrementWaitingTime(ll value)
    {
        waitingTime += value;
        return;
    }
};

Bakery* Test;

// Function to read input from the input file
void readInput(std::string filename)
{
    std::ifstream inputfile(filename);
    inputfile >> n >> k >> l1 >> l2;
    inputfile.close();
    Test = new Bakery(n);  // Initialize the Bakery lock with 'n' threads
}

// testCS function
void testCS(ThreadData *threadData)
{
    int threadId = threadData->getThreadId();

    for(int i = 0; i < k; i++)
    {
        auto reqEnterTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i , "th CS Entry Request at ", getSysTime(reqEnterTime), " by thread ", threadId);

        Test->lock(threadId);
        auto actEnterTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i, "th CS Entry at ", getSysTime(actEnterTime), " by thread ", threadId);

        auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(actEnterTime - reqEnterTime).count();
        threadData->incrementWaitingTime(time_diff);// Increment waiting time

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(Timer(l1))));
        auto reqExitTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i, "th CS Exit Request at ", getSysTime(reqExitTime), " by thread ", threadId);
        Test->unlock(threadId);

        auto actExitTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i, "th CS Exit at ", getSysTime(actExitTime), " by thread ", threadId);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(Timer(l2))));
    }
}

int main(int argc, char *argv[])
{
    readInput(argv[1]);
    auto start_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT("The start time is ", getSysTime(start_time));

    std::vector<std::thread> threads(n);  // Create vector of threads
    std::vector<ThreadData> threadData(n); // Create vector of ThreadData

    for(int i = 0; i < n; i++)
    {
        threadData[i].setThreadId(i);
        threads[i] = std::thread(testCS, &threadData[i]);
    }
    
    for (auto& th : threads) {
        th.join();  // Join all threads to ensure they complete
    }

    auto stop_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT("The stop time is ", getSysTime(stop_time));

    /* ANALYSIS SECTION */
    // For finding maximum and average waiting times
    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();

    float max = 0.0; float avg = 0.0;
    for(auto& data: threadData)
    {
        max = std::max(max, data.getWaitingTime() * 1.0f);
        avg += data.getWaitingTime();
    }
    avg /= (k * n); // per thread, per critical section, avg time
    max /= k; // We selected maximum waiting time for a thread. Divide with number of critical sections to get avg time it waited for a thread

    std::cout << "[Bakery] Throughput, Average, Worst:" << " [" << (k * n * 1.0) / time_diff << ", " << avg << ", " << max << "]\n";

    delete Test;  // Clean up dynamically allocated memory
    return 0;
}