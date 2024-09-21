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
        std::ofstream outputfile("outputs/out.txt", std::ios::app);
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
    static std::default_random_engine generate(std::random_device{}());
    std::exponential_distribution<double> distr(1.0 / lambda);
    return distr(generate);
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
                    if(level[j].load() >= i && victim[i].load() == me)
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
void testCS(int threadId)
{
    for(int i = 0; i < k; i++)
    {
        auto reqEnterTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i , "th CS Entry Request at ", getSysTime(reqEnterTime), " by thread ", threadId);
        Test->lock(threadId);
        auto actEnterTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i, "th CS Entry at ", getSysTime(actEnterTime), " by thread ", threadId);
        sleep(Timer(l1));
        auto reqExitTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i, "th CS Exit Request at ", getSysTime(reqExitTime), " by thread ", threadId);
        Test->unlock(threadId);
        auto actExitTime = std::chrono::high_resolution_clock::now();
        LOGGER.OUTPUT(i, "th CS Exit at ", getSysTime(actExitTime), " by thread ", threadId);
        sleep(Timer(l2));
    }
}

int main(int argc, char *argv[])
{
    readInput(argv[1]);
    auto start_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT("The start time is ", getSysTime(start_time));

    std::vector<std::thread> threads(n);  // Create vector of threads

    for(int i = 0; i < n; i++)
    {
        threads[i] = std::thread(testCS, i);
    }

    for (auto& th : threads) {
        th.join();  // Join all threads to ensure they complete
    }

    auto stop_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT("The stop time is ", getSysTime(stop_time));

    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();
    LOGGER.OUTPUT("Total execution time: ", time_diff, " milliseconds");

    delete Test;  // Clean up dynamically allocated memory
    return 0;
}