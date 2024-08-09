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

class Logger
{
public:
    void DEBUG(std::string str)
    {
        std::ofstream debugfile("debug.txt", std::ios::app);
        debugfile << str << "\n";
        debugfile.close();
    }

    void OUTPUT(std::string str)
    {
        std::ofstream outputfile("out.txt", std::ios::app);
        outputfile << str << "\n";
        outputfile.close();
    }
};

static Logger LOGGER;

void readInput()
{
    std::ifstream inputfile("inp.txt");

    // Your code goes here

    inputfile.close();
    return;
}

int main()
{
    readInput();
    auto start_time = std::chrono::high_resolution_clock::now();

    // Your code goes here
    
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto time_diff = (stop_time - start_time);
    LOGGER.OUTPUT("Total time of Execution: " + std::to_string(time_diff.count()));
    return 0;
}