#include <iostream>
#include <vector>
#include <queue>
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
#include <condition_variable>

// Function to convert time_point to a formatted string
std::string getSysTime(const std::chrono::high_resolution_clock::time_point &tp)
{
    auto time_t = std::chrono::high_resolution_clock::to_time_t(tp);
    std::tm *tm = std::localtime(&time_t); // Convert to local time
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
    return std::string(buffer);
}

int n, p, t;
double alpha;
std::atomic<int> operations(0);

// Start time for time elapsed calculation
std::chrono::high_resolution_clock::time_point start_time;

void readInput(std::string filename)
{
    std::ifstream inputfile(filename);
    inputfile >> n >> p >> t >> alpha;

    inputfile.close();
    return;
}

class Request
{
public:
    bool is_preferred;
    int amount;
    std::condition_variable *cv;
};

class Account
{
public:
    int balance;
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<Request> requestQueue;

    // Constructor
    Account(int initialBalance) : balance(initialBalance) {}

    // Delete copy constructor (mutex and condition_variable are non-copyable)
    Account(const Account &) = delete;
    Account &operator=(const Account &) = delete;

    // Define a move constructor
    Account(Account &&other) noexcept
        : balance(other.balance) {}

    // Define a move assignment operator
    Account &operator=(Account &&other) noexcept
    {
        if (this != &other)
        {
            balance = other.balance;
        }
        return *this;
    }
};

std::vector<Account> accounts;

// Logger class, for printing and logging to log files and debugging
class Logger
{
public:
    template <typename... Args>
    void DEBUG(int thread_id, Args... args)
    {
        std::ofstream debugfile("outputs/debug.txt", std::ios::app);
        std::ostringstream oss;
        (oss << ... << args);
        debugfile << "[" << getSysTime(std::chrono::high_resolution_clock::now()) << "] Th" << thread_id << " - " << oss.str() << "\n";
        debugfile.close();
    }

    template <typename... Args>
    void OUTPUT(int thread_id, Args... args)
    {
        std::ofstream outputfile("outputs/out.txt", std::ios::app);
        std::ostringstream oss;
        (oss << ... << args); // Stream all arguments

        oss << " [";
        for (size_t i = 0; i < accounts.size(); ++i)
        {
            oss << accounts[i].balance;
            if (i != accounts.size() - 1)
                oss << ", ";
        }
        oss << "]";

        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

        outputfile << "[" << getSysTime(current_time) << "] Th" << thread_id << " - " << oss.str()
                   << " Operations done: " << operations.load()  // Number of operations done
                   << " Time elapsed: " << elapsed_time << " ms" // Time elapsed in milliseconds
                   << "\n";
        outputfile.close();
    }
};

static Logger LOGGER;

void processQueue(Account &account, int thread_id)
{
    while (!account.requestQueue.empty())
    {
        Request req = account.requestQueue.front();
        if (account.balance >= req.amount)
        {
            account.requestQueue.pop();
            account.balance -= req.amount;
            req.cv->notify_one(); // Notify the thread that its request has been serviced.
            LOGGER.OUTPUT(thread_id, "Processed a ", req.is_preferred ? "Preferred Withdraw: -" : "Ordinary Withdraw: -", req.amount);
        }
        else
        {
            // Exit the loop if the front request cannot be serviced.
            break;
        }
    }
}

void deposit(Account &account, int amount, int thread_id)
{
    std::unique_lock<std::mutex> lock(account.mtx);
    account.balance += amount;
    LOGGER.OUTPUT(thread_id, "Requested a Deposit of ", amount, " to account");
    account.cv.notify_all();          // Notify all waiting threads about the balance update.
    processQueue(account, thread_id); // Process the queue after the deposit.
    operations.fetch_add(1);
}

void withdraw(Account &account, int amount, bool is_preferred, int thread_id)
{
    std::unique_lock<std::mutex> lock(account.mtx);
    std::condition_variable local_cv;
    Request request = {is_preferred, amount, &local_cv};

    account.requestQueue.push(request);
    LOGGER.OUTPUT(thread_id, "Requested a ", is_preferred ? "Preferred Withdraw: -" : "Ordinary Withdraw: -", amount);

    while (true)
    {
        if (!account.requestQueue.empty() && account.requestQueue.front().cv == &local_cv && account.balance >= amount)
        {
            account.requestQueue.pop();
            account.balance -= amount;
            LOGGER.OUTPUT(thread_id, is_preferred ? "Preferred Withdraw: -" : "Ordinary Withdraw: -", amount, " completed");
            operations.fetch_add(1);

            return; // Exit once the request is processed.
        }
        // Wait until the queue state changes.
        local_cv.wait(lock);
    }
}

std::vector<std::pair<int, int>> transactions = {{0, 50}, {1, 50}, {0, 30}, {1, 30}, {0, 70}, {1, 70}, {0, 20}, {1, 20}, {0, 100}, {1, 100}};

void threadFunc(int id, int t, double alpha, int p)
{
    std::default_random_engine generator;
    std::exponential_distribution<double> dist(alpha);

    for (int i = 0; i < t; ++i)
    {
        int account_id = rand() % p;
        int operation = (rand() % 10 < 7) ? 0 : 1;                                // 70% probability for deposit, 30% for withdraw
        int amount = (operation == 0) ? (rand() % 100 + 20) : (rand() % 100 + 1); // Deposits are slightly larger

        if (operation == 0)
        {
            LOGGER.OUTPUT(id, "Requests for a deposit of amount ", amount, " into account ", account_id);
            deposit(accounts[account_id], amount, id);
        }
        else
        {
            LOGGER.OUTPUT(id, "Requests for a withdrawal of amount ", amount, " from account ", account_id);
            bool is_preferred = rand() % 2;
            withdraw(accounts[account_id], amount, is_preferred, id);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dist(generator) * 1000)));
    }
}

int main(int argc, char *argv[])
{
    readInput(argv[1]);
    start_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT(0, "Input: ", argv[1]);
    LOGGER.OUTPUT(0, "The start time is");

    for (int i = 0; i < p; ++i)
    {
        accounts.emplace_back(0);
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < n; ++i)
    {
        threads.emplace_back(threadFunc, i + 1, t, alpha, p);
    }

    for (auto &th : threads)
    {
        th.join();
    }

    auto stop_time = std::chrono::high_resolution_clock::now();
    LOGGER.OUTPUT(0, "The stop time is");

    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();
    LOGGER.OUTPUT(0, "Total execution time: ", time_diff, " milliseconds");

    std::cout << time_diff << " " << operations << " " << t;

    return 0;
}
