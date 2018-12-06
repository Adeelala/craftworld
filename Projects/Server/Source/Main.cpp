#include <memory>

#include <memory>
#include <iostream>
#include <boost/asio.hpp>

#include "World.hpp"

using boost::asio::ip::tcp;

CraftWorld::World createTestWorld() {

}

int main(int argc, char* argv[]) {
	std::cout << "Starting server..." << std::flush;

	CraftWorld::World world({ 8, 8, 8 }, { 8, 8, 8 });

	boost::asio::io_service ioService;

	try {
		tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 8000));
		tcp::socket socket(ioService);
		acceptor.accept(socket);
		std::string message = "Hello world!";
		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
