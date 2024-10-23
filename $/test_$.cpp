#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>

using boost::asio::ip::tcp;
namespace asio = boost::asio;

// Utility template to handle repetitive operations
template <typename T>
class Property
{
public:
    Property(T value) : value_(value) {}
    T get() const { return value_; }
    void set(T value) { value_ = value; }
private:
    T value_;
};

// Account class definition
class Account
{
public:
    Account(std::string owner, double initial_balance)
        : owner_(owner), balance_(initial_balance) {}

    std::string getOwner() const { return owner_.get(); }
    double getBalance() const { return balance_.get(); }
    bool deposit(double amount)
    {
        if (amount < 0)
            return false;
        balance_.set(balance_.get() + amount);
        return true;
    }

    bool withdraw(double amount)
    {
        if (amount < 0 || amount > balance_.get())
            return false;
        balance_.set(balance_.get() - amount);
        return true;
    }

private:
    Property<std::string> owner_;
    Property<double> balance_;
};

// Banking server-client communication (using Boost Asio)
class BankingServer
{
public:
    BankingServer(asio::io_context &io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        auto new_session = std::make_shared<tcp::socket>(acceptor_.get_io_context());
        acceptor_.async_accept(*new_session, [this, new_session](const boost::system::error_code &error) {
            if (!error)
            {
                handle_session(new_session);
            }
            start_accept();
        });
    }

    void handle_session(std::shared_ptr<tcp::socket> socket)
    {
        auto self = this;
        asio::async_read_until(*socket, asio::dynamic_buffer(buffer_), '\n',
                               [this, self, socket](const boost::system::error_code &error, std::size_t) {
                                   if (!error)
                                   {
                                       std::cout << "Received transaction request: " << buffer_ << std::endl;
                                       buffer_.clear();
                                   }
                               });
    }

    tcp::acceptor acceptor_;
    std::string buffer_;
};

class BankingClient
{
public:
    BankingClient(asio::io_context &io_context, const std::string &host, const std::string &port)
        : socket_(io_context)
    {
        tcp::resolver resolver(io_context);
        asio::connect(socket_, resolver.resolve(host, port));
    }

    void sendTransaction(const std::string &transaction)
    {
        asio::write(socket_, asio::buffer(transaction + "\n"));
    }

private:
    tcp::socket socket_;
};

// Main function to demonstrate creating accounts and transactions
int main()
{
    try
    {
        // Create accounts
        Account account1("Alice", 1000.0);
        Account account2("Bob", 500.0);

        std::cout << "Initial Balances:\n";
        std::cout << "Alice: " << account1.getBalance() << "\n";
        std::cout << "Bob: " << account2.getBalance() << "\n";

        // Perform transaction from Alice to Bob
        double transfer_amount = 200.0;
        if (account1.withdraw(transfer_amount))
        {
            account2.deposit(transfer_amount);
            std::cout << "Transaction Successful: Alice sent " << transfer_amount << " to Bob.\n";
        }
        else
        {
            std::cout << "Transaction Failed: Insufficient funds.\n";
        }

        std::cout << "Updated Balances:\n";
        std::cout << "Alice: " << account1.getBalance() << "\n";
        std::cout << "Bob: " << account2.getBalance() << "\n";

        // Start server-client demonstration
        asio::io_context io_context;
        BankingServer server(io_context, 12345);

        std::thread server_thread([&io_context]() { io_context.run(); });

        // Give the server a moment to start
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Client sends a transaction message
        BankingClient client(io_context, "127.0.0.1", "12345");
        client.sendTransaction("Transfer 100 from Alice to Bob");

        server_thread.join();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

