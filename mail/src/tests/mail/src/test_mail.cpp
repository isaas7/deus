#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <boost/asio.hpp>

#define SERVER_PORT 2525
#define MAX_BUFFER_SIZE 1024

using namespace boost::asio;
using ip::tcp;
using ip::udp;

// Template for a generic server class

template <typename ProtocolType>
class MailServer
{
public:
    MailServer(io_service &ioService, unsigned short port) : socket_(ioService, typename ProtocolType::endpoint(ProtocolType::v4(), port))
    {
        start();
    }

private:
    void start();

    typename ProtocolType::socket socket_;
};

// Macro to define the behavior for a TCP connection
#define HANDLE_TCP_SESSION(session)                                    \
    do                                                                \
    {                                                                 \
        std::thread([session]() { handleTCPConnection(session); }).detach(); \
    } while (0)

void handleTCPConnection(std::shared_ptr<tcp::socket> socket)
{
    try
    {
        char data[MAX_BUFFER_SIZE];
        boost::system::error_code error;
        size_t length = socket->read_some(boost::asio::buffer(data), error);
        if (!error)
        {
            std::cout << "Received TCP message: " << std::string(data, length) << std::endl;
            // Echo back the message
            socket->write_some(boost::asio::buffer(data, length));
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in TCP session: " << e.what() << std::endl;
    }
}

// Specialization for TCP

template <>
void MailServer<tcp>::start()
{
    auto session = std::make_shared<tcp::socket>(std::move(socket_));
    HANDLE_TCP_SESSION(session);
}

// Specialization for UDP

template <>
void MailServer<udp>::start()
{
    auto receiveHandler = [this](const boost::system::error_code &error, std::size_t bytesReceived) {
        if (!error)
        {
            std::cout << "Received UDP message" << std::endl;
            // Process the UDP message
            socket_.async_receive_from(
                boost::asio::buffer(data_, MAX_BUFFER_SIZE), senderEndpoint_,
                receiveHandler);
        }
    };
    socket_.async_receive_from(boost::asio::buffer(data_, MAX_BUFFER_SIZE), senderEndpoint_, receiveHandler);
}

int main()
{
    try
    {
        io_service ioService;

        // Run TCP MailServer
        MailServer<tcp> tcpMailServer(ioService, SERVER_PORT);

        // Run UDP MailServer
        MailServer<udp> udpMailServer(ioService, SERVER_PORT + 1);

        ioService.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

