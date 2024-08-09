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

int N;      // Number of rows of matrix
float S;    // Sparsity of the matrix
int K;      // Number of threads to be used
int rowInc; // rowInc for dynamic algorithm

int **Matrix;

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
    inputfile >> N >> S >> K >> rowInc;

    Matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        Matrix[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inputfile >> Matrix[i][j];
        }
    }

    inputfile.close();
    return;
}

class ThreadData
{
    int threadId;
    int numZeroes;

public:
    ThreadData()
    {
        threadId = 0;
        numZeroes = 0;
    }

    int getThreadId()
    {
        return threadId;
    }

    void setThreadId(int tid)
    {
        this->threadId = tid;
    }

    void setNumZeroes(int numZeroes)
    {
        this->numZeroes = numZeroes;
    }

    int getNumZeroes()
    {
        return numZeroes;
    }

    void incrementNumberOfZeroes(int value)
    {
        numZeroes += value;
        return;
    }
};

int findNumberofZeroesInRow(int x)
{
    LOGGER.DEBUG("Entered findNumberofZeroesInRow Function");
    int numberOfZeroElements = 0;
    for (int i = 0; i < N; i++)
    {
        if (Matrix[x][i] == 0) // For x-th row, i-th column
        {
            numberOfZeroElements++;
        }
    }

    LOGGER.DEBUG("Exited the findNumberofZeroesInRow Function");

    return numberOfZeroElements;
}

/*Should be changed */
void threadFunc(ThreadData *threadData)
{
    int tid = threadData->getThreadId();
    int p = N / K;
    LOGGER.DEBUG(std::to_string(tid) + " entered threadFunc Function");
    
    for (int i = 0; i < N; i++)
    {
        if (i % N == tid)
        {
            LOGGER.DEBUG("Row Number: " + std::to_string(i));
            int thisRowZeroes = findNumberofZeroesInRow(i);
            threadData->incrementNumberOfZeroes(thisRowZeroes);
        }
    }

    LOGGER.DEBUG("Exited the threadFunc Function");
}

int main()
{
    readInput();
    auto start_time = std::chrono::high_resolution_clock::now();

    ThreadData threadData[N];
    std::thread threads[N];

    for (int i = 0; i < N; i++)
    {
        threadData[i].setThreadId(i);
        threads[i] = std::thread(threadFunc, &threadData[i]);
    }

    int numZeroesInMatrix = 0;
    for (int i = 0; i < N; i++)
    {
        threads[i].join();
        numZeroesInMatrix += threadData[i].getNumZeroes();
    }

    std::cout << "Sparsity = " << numZeroesInMatrix * 0.1 / (N * N) << "\n";
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto time_diff = (stop_time - start_time);
    LOGGER.OUTPUT("Total time of Execution: " + std::to_string(time_diff.count()));
    return 0;
}