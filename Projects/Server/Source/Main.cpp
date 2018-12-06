#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "World.hpp"

using boost::asio::ip::tcp;

class connection : public boost::enable_shared_from_this<connection> {
public:
    typedef boost::shared_ptr<connection> pointer;

    static pointer create(boost::asio::io_context& io_context) {
        return pointer(new connection(io_context));
    }

    tcp::socket& socket() {
        return socket_;
    }

    // Handle the client (currently just sends "Hello world!")
    void start() {
    	std::cout << "Made a connection!" << std::endl;
        message_="Hello world!";
        boost::asio::async_write(socket_, boost::asio::buffer(message_), boost::bind(&connection::handle_write,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

private:
    connection(boost::asio::io_context& io_context) : socket_(io_context) {}

    // Handles the rest of the client connection
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred) {}

    tcp::socket socket_;
    std::string message_;
};

class server {
public:
    // The server will listen on the specified port
    server(boost::asio::io_context& io_context) : acceptor_(io_context, tcp::endpoint(tcp::v4(), 8000)) {
        start_accept();
    }

private:
    // Create a socket and initiate an asynchronous accept operation that waits for new connections
    void start_accept() {
        connection::pointer new_connection = connection::create(acceptor_.get_executor().context());
        acceptor_.async_accept(new_connection->socket(), boost::bind(&server::handle_accept, this, new_connection,
                boost::asio::placeholders::error));
    }

    // Asynchronously handles the client request and calls start_accept again to start accepting new connections
    void handle_accept(connection::pointer new_connection, const boost::system::error_code& error) {
        if(!error)
            new_connection->start();

        start_accept();
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
	std::cout << "Starting server..." << std::endl;

    try {
        // Create the server object that is going to accept connections
        boost::asio::io_context io_context;
        server server(io_context);
        // Run the IO context so that it will perform asynchronous operations
        io_context.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
