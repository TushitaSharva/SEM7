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
        std::ofstream debugfile("debug_dynamic.txt", std::ios::app);
        debugfile << str << "\n";
        debugfile.close();
    }

    void OUTPUT(std::string str)
    {
        std::ofstream outputfile("out_dynamic.txt", std::ios::app);
        outputfile << str << "\n";
        outputfile.close();
    }
};

static Logger LOGGER;

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
    LOGGER.DEBUG("Entered findNumberofZeroesInRow Function " + std::to_string(x));
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

class Counter
{
    int rowsDone;
    std::mutex mut;

public:
    Counter()
    {
        rowsDone = 0;
    }
    bool request(ThreadData *threadData)
    {
        LOGGER.DEBUG(std::to_string(threadData->getThreadId()) + " entered request Method");
        mut.lock();
        int curr = rowsDone;
        if (curr >= N - 1)
        {
            mut.unlock();
            return false;
        }

        int k = std::min(rowsDone + rowInc, N);
        rowsDone = k;
        LOGGER.DEBUG("rowsDone = " + std::to_string(rowsDone));
        mut.unlock();

        for (int i = curr; i < k; i++)
        {
            LOGGER.DEBUG(std::to_string(threadData->getThreadId()) + " entered calculating zeroes of " + std::to_string(i));
            int zeroesOfThisRow = findNumberofZeroesInRow(i);
            threadData->incrementNumberOfZeroes(zeroesOfThisRow);
        }

        LOGGER.DEBUG(std::to_string(threadData->getThreadId()) + " exited request Method");
        return true;
    }
};

Counter *counter;

void init()
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

    counter = new Counter;
    return;
}

void threadFunc(ThreadData *threadData)
{
    int tid = threadData->getThreadId();
    int p = N / K;
    LOGGER.DEBUG(std::to_string(tid) + " entered threadFunc Function");
    bool shouldContinue = true;

    while (shouldContinue)
    {
        shouldContinue = counter->request(threadData);
    }

    LOGGER.DEBUG("Exited the threadFunc Function");
}

int main()
{
    init();
    auto start_time = std::chrono::high_resolution_clock::now();

    ThreadData threadData[K];
    std::thread threads[K];

    for (int i = 0; i < K; i++)
    {
        threadData[i].setThreadId(i);
        threads[i] = std::thread(threadFunc, &threadData[i]);
    }

    int numZeroesInMatrix = 0;
    for (int i = 0; i < K; i++)
    {
        threads[i].join();
        LOGGER.DEBUG(std::to_string(threadData[i].getThreadId()) + " zeroes: " + std::to_string(threadData[i].getNumZeroes()));
        numZeroesInMatrix += threadData[i].getNumZeroes();
    }

    auto done = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(done-start_time).count();
    LOGGER.OUTPUT("Time taken to count the number of zeroes: " + std::to_string(milliseconds) + "ms");
    LOGGER.OUTPUT("Number of zero-valued elements in the matrix: " + std::to_string(numZeroesInMatrix));
    LOGGER.OUTPUT("Percentage Sparsity: " + std::to_string((numZeroesInMatrix * 1.0 / (N * N)) * 100) + "%");
    for(int i = 0; i < K; i++)
    {
        LOGGER.OUTPUT("Number of zero-valued elements counted by thread " + std::to_string(i) + ": " + std::to_string(threadData[i].getNumZeroes()));
    }
    return 0;
}