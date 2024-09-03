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
#include <omp.h>

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

void threadFunc(ThreadData *threadData, int rowToWork)
{
    int tid = threadData->getThreadId();
    int thisRowZeroes = findNumberofZeroesInRow(rowToWork);
    threadData->incrementNumberOfZeroes(thisRowZeroes);
}

int main()
{
    readInput();
    auto start_time = std::chrono::system_clock::now();

    ThreadData threadData[K];
    int numZeroesInMatrix = 0;

    for (int i = 0; i < K; i++)
    {
        threadData[i].setThreadId(i);
    }

#pragma omp parallel for num_threads(K)
    for (int i = 0; i < N; i++)
    {
        LOGGER.DEBUG("Inside omp parallel, i = "+std::to_string(i));
        threadFunc(&threadData[i], i);
    }

    for (int i = 0; i < K; i++)
        numZeroesInMatrix += threadData[i].getNumZeroes();

    auto done = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(done - start_time).count();
    LOGGER.OUTPUT("Time taken to count the number of zeroes: " + std::to_string(milliseconds) + "ms");
    std::cout << "Chunk: " + std::to_string(milliseconds) + "ms\n";
    LOGGER.OUTPUT("Number of zero-valued elements in the matrix: " + std::to_string(numZeroesInMatrix));
    LOGGER.OUTPUT("Percentage Sparsity: " + std::to_string((numZeroesInMatrix * 1.0 / (N * N)) * 100) + "%");
    for (int i = 0; i < K; i++)
    {
        LOGGER.OUTPUT("Number of zero-valued elements counted by thread " + std::to_string(i) + ": " + std::to_string(threadData[i].getNumZeroes()));
    }
    return 0;
}