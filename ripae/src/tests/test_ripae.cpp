#include <boost/version.hpp>
#include <cstdint>
#include <stdexcept>

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

// Account Class Template
template <typename T>
class Account {
public:
    Account() : id_(0), balance_(0.0) {}  // Default constructor
    Account(uint64_t id, double balance) : id_(id), balance_(balance) {}
    uint64_t getId() const { return id_.get(); }
    double getBalance() const { return balance_.get(); }
    void setBalance(double balance) { balance_.set(balance); }

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

private:
    Utility<uint64_t> id_;
    Stack<Account<T>> accounts_;
};

int main(int argc, char** argv) {
    // Example Usage
    Account<int> account1(1001, 5000.0);
    account1.setBalance(6000.0);

    Bank<int> bank(1);
    bank.addAccount(account1);

    return 0;
}

