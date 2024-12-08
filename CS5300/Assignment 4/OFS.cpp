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
#include <time.h>
#include <chrono>
#include <fstream>
#include <atomic>
#include <mutex>
#include <thread>

// Logger class, for printing and logging to log files and debugging
class Logger
{
public:
    template<typename... Args>
    void DEBUG(Args... args)
    {
        std::ofstream debugfile("debug.txt", std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);  // Use fold expression to stream all arguments
        debugfile << oss.str() << "\n";
        debugfile.close();
    }

    template<typename... Args>
    void OUTPUT(Args... args)
    {
        std::ofstream outputfile("out.txt", std::ios::app);
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

// Global variables required
static Logger LOGGER;
int nw; // Number of writer collector threads
int ns; // Number of Snapshot collector threads
int M; // Snapshot object size
float muw; // Parameter for sleep of writer threads
float mus; // Parameter for sleep of snapshot threads
int k; // Number of snapshots to be collected
std::atomic<bool> term; // A variable to inform the writer threads to terminate

template<class T>
class StampedValue {
public:
    T value;
    long stamp;

    StampedValue(T init) {
        stamp = 0;
        value = init;
    }

    StampedValue(long ts, T v) {
        stamp = ts;
        value = v;
    }

    static StampedValue max(StampedValue x, StampedValue y) {
        if(x.stamp > y.stamp){
            return x;
        } else {
            return y;
        }
    }
};

template<class T> using tablePointers = std::unique_ptr<std::atomic<StampedValue<T>>>;

template<typename T>
class OFSnapShot{
    tablePointers a_table;
public:
    OFSnapShot(int capacity, T init) {
        a_table = (std::unique_ptr<std::atomic<StampedValue<T>>>[]) new std::unique_ptr<std::atomic<StampedValue<T>>>(capacity);
    }

    void update(int l, T v, int tid) {
        
    }
};

OFSnapShot<int> snapObj(M, 0);

void readInput(std::string filename){
    std::ifstream inputfile(filename);
    inputfile >> nw >> ns >> M >> muw >> mus >> k;
    inputfile.close();
    return;
}

int main(int argc, char* argv[])
{
    readInput(argv[0]);
    auto start_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT("The start time is ", getSysTime(start_time));

    // Your code goes here

    auto stop_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT("The stop time is ", getSysTime(stop_time));

    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();
    LOGGER.OUTPUT("Total execution time: ", time_diff, " milliseconds");

    return 0;
}