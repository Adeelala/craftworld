#include <iostream>
#include <boost/asio.hpp>

#include "World.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	std::cout << "Starting server...";

	CraftWorld::World world;

	try
    {
	    boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8000));
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        std::string message = "Hello world!";
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
	}
	catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

	return 0;
}
