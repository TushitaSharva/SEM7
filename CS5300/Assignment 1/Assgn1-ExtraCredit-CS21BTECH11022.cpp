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
std::mutex mut1; // mutex lock for subgrid 1
std::mutex mut2; // mutex lock for subgrid 2
std::mutex mut3; // mutex lock for subgrid 3
std::mutex mut4; // mutex lock for subgrid 4

class Logger
{
public:
    void DEBUG(std::string str)
    {
        std::ofstream debugfile("outputs/debug_dynamic.txt", std::ios::app);
        debugfile << str << "\n";
        debugfile.close();
    }

    void OUTPUT(std::string str)
    {
        std::ofstream outputfile("outputs/out_extra_credit.txt", std::ios::app);
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
        this->numZeroes += value;
        return;
    }
};

int findNumZeroesInSubGrid(int rowOffset, int row, int colOffset)
{
    int counter = 0;

    for(int i = 0; i < N/2; i++)
    {
        if(Matrix[rowOffset + row][colOffset + i] == 0)
        {
            counter++;
        }
    }    

    return counter;
}

class Counter
{
    int firstSubGrid; // shared member for first subgrid
    int secondSubGrid; // shared member for second subgrid
    int thirdSubGrid; // shared member for third subgrid
    int fourthSubGrid; // shared member for fourth subgrid

public:
    Counter()
    {
        firstSubGrid = 0;
        secondSubGrid = 0;
        thirdSubGrid = 0;
        fourthSubGrid = 0;
    }

    bool request(ThreadData *threadData)
    {
        int threadId = threadData->getThreadId();

        if(threadId < K/4) {
            return requestFirstSubgrid(threadData);
        }
        else if(threadId < K/2) {
            return requestSecondSubgrid(threadData);
        }
        else if(threadId < 3 * K / 4) {
            return requestThirdSubgrid(threadData);
        }
        else if(threadId < K) {
            return requestFourthSubgrid(threadData);
        }

        return false;
    }

    bool requestFirstSubgrid(ThreadData *threadData)
    {
        mut1.lock();
        int curr = firstSubGrid;
        if (curr >= N/2)
        {
            mut1.unlock();
            return false;
        }

        int k = std::min(firstSubGrid + rowInc, N / 2);
        firstSubGrid = k;
        mut1.unlock();

        for (int i = curr; i < k; i++)
        {
            int zeroesOfThisRow = findNumZeroesInSubGrid(0, i, 0);
            threadData->incrementNumberOfZeroes(zeroesOfThisRow);
        }
        return true;
    }

    bool requestSecondSubgrid(ThreadData *threadData)
    {
        mut2.lock();
        int curr = secondSubGrid;
        if (curr >= N/2)
        {
            mut2.unlock();
            return false;
        }

        int k = std::min(secondSubGrid + rowInc, N / 2);
        secondSubGrid = k;
        mut2.unlock();

        for (int i = curr; i < k; i++)
        {
            int zeroesOfThisRow = findNumZeroesInSubGrid(0, i, N/2);
            threadData->incrementNumberOfZeroes(zeroesOfThisRow);
        }
        return true;
    }

    bool requestThirdSubgrid(ThreadData *threadData)
    {
        mut3.lock();
        int curr = thirdSubGrid;
        if (curr >= N/2)
        {
            mut3.unlock();
            return false;
        }

        int k = std::min(thirdSubGrid + rowInc, N / 2);
        thirdSubGrid = k;
        mut3.unlock();

        for (int i = curr; i < k; i++)
        {
            int zeroesOfThisRow = findNumZeroesInSubGrid(N/2, i, 0);
            threadData->incrementNumberOfZeroes(zeroesOfThisRow);
        }
        return true;
    }

    bool requestFourthSubgrid(ThreadData *threadData)
    {
        mut4.lock();
        int curr = fourthSubGrid;
        if (curr >= N/2)
        {
            mut4.unlock();
            return false;
        }

        int k = std::min(fourthSubGrid + rowInc, N / 2);
        fourthSubGrid = k;
        mut4.unlock();

        for (int i = curr; i < k; i++)
        {
            int zeroesOfThisRow = findNumZeroesInSubGrid(N/2, i, N/2);
            threadData->incrementNumberOfZeroes(zeroesOfThisRow);
        }

        return true;
    }
};

static Counter *counter;

void init()
{
    std::ifstream inputfile("5000-80.txt");;
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
    bool shouldContinue = true;

    while (shouldContinue)
    {
        shouldContinue = counter->request(threadData);
    }

    return;
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
        numZeroesInMatrix += threadData[i].getNumZeroes();
    }

    auto done = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(done - start_time).count();
    LOGGER.OUTPUT("Time taken to count the number of zeroes: " + std::to_string(milliseconds) + "ms");
    std::cout << "Extra Credit: " + std::to_string(milliseconds) + "ms\n";
    LOGGER.OUTPUT("Number of zero-valued elements in the matrix: " + std::to_string(numZeroesInMatrix));
    LOGGER.OUTPUT("Percentage Sparsity: " + std::to_string((numZeroesInMatrix * 1.0 / (N * N)) * 100) + "%");
    for (int i = 0; i < K; i++)
    {
        LOGGER.OUTPUT("Number of zero-valued elements counted by thread " + std::to_string(i) + ": " + std::to_string(threadData[i].getNumZeroes()));
    }
    return 0;
}