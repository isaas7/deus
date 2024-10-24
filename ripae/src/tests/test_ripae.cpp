#include <boost/version.hpp>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

#define LOG_FAILURE(message) std::cerr << "[ERROR] " << message << "\n";
#define LOG_SUCCESS(message) std::cout << "[SUCCESS] " << message << "\n";

std::mutex mtx;

// Utility Class Template
template <typename T>
class Utility {
public:
    Utility(T value) : value_(value) {}
    T get() const { return value_; }
    void set(T value) { value_ = value; }
private:
    T value_;
};

// Account Class Template
template <typename T>
class Account {
public:
    Account() : id_(0), balance_(0.0) {}  // Default constructor
    Account(uint64_t id, double balance) : id_(id), balance_(balance) {}
    uint64_t getId() const { return id_.get(); }
    double getBalance() const { return balance_.get(); }
    void setBalance(double balance) { balance_.set(balance); }

    bool withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balance_.get() >= amount) {
            balance_.set(balance_.get() - amount);
            return true;
        } else {
            return false;
        }
    }

    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance_.set(balance_.get() + amount);
    }

private:
    Utility<uint64_t> id_;
    Utility<double> balance_;
};

// Stack Class Template
template <typename T>
class Stack {
public:
    Stack() : top_(-1) {}
    bool isEmpty() const { return top_ == -1; }
    void push(const T& value) {
        if (top_ >= max_size - 1) {
            throw std::overflow_error("Stack overflow");
        }
        data_[++top_] = value;
    }
    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow");
        }
        --top_;
    }
    T& top() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data_[top_];
    }
    const T& top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data_[top_];
    }

    // New method to access an element at a specific index
    T& at(int index) {
        if (index < 0 || index > top_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

private:
    static const int max_size = 100;
    T data_[max_size];
    int top_;
};

// Bank Class Template
template <typename T>
class Bank {
public:
    Bank(uint64_t id) : id_(id) {}
    uint64_t getId() const { return id_.get(); }
    const Stack<Account<T>>& getAccounts() const { return accounts_; }
    void addAccount(const Account<T>& account) { accounts_.push(account); }

    Account<T>& getAccount(int index) {
        return accounts_.at(index);
    }

private:
    Utility<uint64_t> id_;
    Stack<Account<T>> accounts_;
};

int main(int argc, char** argv) {
    // Create a bank and a large set of accounts
    Bank<int> bank(1);
    const int num_accounts = 50;

    // Initialize accounts with varying balances
    for (int i = 0; i < num_accounts; ++i) {
        double initial_balance = (i + 1) * 1000.0; // Varying balances
        bank.addAccount(Account<int>(1000 + i, initial_balance));
    }

    // Function to perform transactions
    auto transaction = [&](int account_index, double amount, bool idempotent) {
        try {
            Account<int>& account = bank.getAccount(account_index);
            if (account.withdraw(amount)) {
                LOG_SUCCESS("Withdrawal of " << amount << " from Account " << account.getId() << " succeeded.");
            } else {
                LOG_FAILURE("Withdrawal of " << amount << " from Account " << account.getId() << " failed. Insufficient balance.");
                if (idempotent) {
                    LOG_SUCCESS("Retrying withdrawal as an idempotent operation.");
                    account.withdraw(amount / 2); // Retry with a smaller amount
                }
            }
        } catch (const std::exception& e) {
            LOG_FAILURE("Transaction failed: " << e.what());
        }
    };

    // Create threads to perform transactions concurrently
    std::vector<std::thread> threads;
    for (int i = 0; i < num_accounts; ++i) {
        threads.emplace_back(transaction, i, 500.0 * (i % 3 + 1), i % 2 == 0); // Varying amounts and idempotency
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

