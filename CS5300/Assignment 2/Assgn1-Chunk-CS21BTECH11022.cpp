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
        std::ofstream debugfile("outputs/debug_chunk.txt", std::ios::app);
        debugfile << str << "\n";
        debugfile.close();
    }

    void OUTPUT(std::string str)
    {
        std::ofstream outputfile("outputs/out_chunk.txt", std::ios::app);
        outputfile << str << "\n";
        outputfile.close();
    }
};

static Logger LOGGER;

void readInput()
{
    std::ifstream inputfile("5000-80.txt");
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
    int start;
    int numWorks;

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

    int getNumWorks()
    {
        return numWorks;
    }

    void setNumWorks(int x)
    {
        this->numWorks = x;
    }

    int getStart()
    {
        return start;
    }

    void setStart(int x)
    {
        this->start = x;
    }
};

int findNumberofZeroesInRow(int x)
{
    int numberOfZeroElements = 0;
    for (int i = 0; i < N; i++)
    {
        if (Matrix[x][i] == 0) // For x-th row, i-th column
        {
            numberOfZeroElements++;
        }
    }

    return numberOfZeroElements;
}

void threadFunc(ThreadData *threadData)
{
    int tid = threadData->getThreadId();
    int start = threadData->getStart();
    int totalWorks = threadData->getNumWorks();

    for (int i = start; i < start + totalWorks; i++)
    {
        int thisRowZeroes = findNumberofZeroesInRow(i);
        threadData->incrementNumberOfZeroes(thisRowZeroes);
    }
}

int main()
{
    readInput();
    auto start_time = std::chrono::system_clock::now();

    ThreadData threadData[K];
    std::thread threads[K];

    int quotient = N/K;
    int remainder = N % K;

    for (int i = 0; i < remainder; i++)
    {
        threadData[i].setThreadId(i);
        threadData[i].setNumWorks(quotient + 1);
        threadData[i].setStart((quotient + 1) * i);
        threads[i] = std::thread(threadFunc, &threadData[i]);
    }

    for (int i = remainder; i < K; i++)
    {
        threadData[i].setThreadId(i);
        threadData[i].setNumWorks(quotient);
        threadData[i].setStart(((quotient + 1) * remainder) + (quotient) * (i - remainder));
        threads[i] = std::thread(threadFunc, &threadData[i]);
    }

    int numZeroesInMatrix = 0;
    for (int i = 0; i < K; i++)
    {
        threads[i].join();
        numZeroesInMatrix += threadData[i].getNumZeroes();
    }

    auto done = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(done-start_time).count();
    LOGGER.OUTPUT("Time taken to count the number of zeroes: " + std::to_string(milliseconds) + "ms");
    std::cout << "Chunk: " + std::to_string(milliseconds) + "ms\n";
    LOGGER.OUTPUT("Number of zero-valued elements in the matrix: " + std::to_string(numZeroesInMatrix));
    LOGGER.OUTPUT("Percentage Sparsity: " + std::to_string((numZeroesInMatrix * 1.0 / (N * N)) * 100) + "%");
    for(int i = 0; i < K; i++)
    {
        LOGGER.OUTPUT("Number of zero-valued elements counted by thread " + std::to_string(i) + ": " + std::to_string(threadData[i].getNumZeroes()));
    }
    return 0;
}