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
        std::ofstream outputfile("outputs/out_filter.txt", std::ios::app);
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
class Filter
{
    std::atomic<int> *level;
    std::atomic<int> *victim;

public:
    Filter(int n)
    {
        level = new std::atomic<int>[n];
        victim = new std::atomic<int>[n];
        for(int i = 0; i < n; i++)
        {
            level[i] = 0;
        }
    }

    void lock(int threadId)
    {
        int me = threadId;
        for(int i = 1; i < n; i++)
        {
            level[me].store(i);
            victim[i].store(me);

            for(int j = 0; j < n; j++)
            {
                if(j != me)
                {
                    while(level[j].load() >= i && victim[i].load() == me)
                    {
                        // Bounded wait
                    }
                }
            }
        }
    }

    void unlock(int threadId)
    {
        int me = threadId;
        level[me].store(0);
    }

    ~Filter() {
        delete[] level;
        delete[] victim;
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

Filter* Test;

// Function to read input from the input file
void readInput(std::string filename)
{
    std::ifstream inputfile(filename);
    inputfile >> n >> k >> l1 >> l2;
    inputfile.close();
    Test = new Filter(n);  // Initialize the Bakery lock with 'n' threads
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

    ll max = 0, avg = 0;
    for(auto& data: threadData)
    {
        max = std::max(max, data.getWaitingTime());
        avg += data.getWaitingTime();
    }
    avg /= n;

    std::cout << "[Filter] Throughput, Average, Worst:" << " [" << (k * n * 1.0) / time_diff << ", " << avg << ", " << max << "]\n";

    delete Test;  // Clean up dynamically allocated memory
    return 0;
}