#include "Client.hpp"

#include <iterator>
#include <iostream>
#include <boost/serialization/shared_ptr.hpp>

#include "Actions/ConnectAction.hpp"

namespace CraftWorld {
	Client::Client(const std::string& host, const int& port) : socket_(
		[&]() {
			// Initialize IO context
			boost::asio::io_context ioContext;

			// Resolve server endpoint
			tcp::resolver::results_type endpoints = tcp::resolver(ioContext).resolve(host, std::to_string(port));

			// Create new socket
			tcp::socket socket(ioContext);

			// Establish a connection
			try {
				boost::asio::connect(socket, endpoints);
			} catch(std::exception& e) {
				std::cerr << e.what() << std::endl;

				exit(1);
			}

			return socket;
		}()
	) {
	}

	void Client::readLoop(const std::function<void(const std::string&)>& dataHandler) {
        while(true) {
            // Receive data
            std::string data;
            boost::system::error_code errorCode;
            size_t length = boost::asio::read_until(socket_, boost::asio::dynamic_buffer(data), "\n\n", errorCode);
            data = data.substr(0, length - 2);

            // Check if data was received
            if(errorCode == boost::asio::error::eof) {
                // The connection was closed, so exit
                exit(0);
            } else if(errorCode) {
                // An error occurred
                throw boost::system::system_error(errorCode);
            }

            // Handle data
            std::cout << "Received data: " << std::endl << data << std::endl;
            dataHandler(data);
        }
	}

	void Client::writeLoop() {
	    // TODO: send ConnectAction to server
        std::stringstream stringStream;
        boost::archive::text_oarchive archive(stringStream);
		archive.register_type(static_cast<Actions::ConnectAction*>(nullptr));
        auto connectAction = std::make_shared<Actions::ConnectAction>(-1, username_);
		archive << BOOST_SERIALIZATION_NVP(connectAction);
        boost::system::error_code ignored_error;
        std::cout << "Sending: " << stringStream.str() << std::endl;
        boost::asio::write(socket_, boost::asio::buffer(stringStream.str() + "\n\n"),ignored_error);

	    while(true)
        {
	        // TODO: put client game decision making here and write it to the server, remove the break when done

	        // Just wrote something to the server, wait 10 milliseconds in order to avoid server overloading
            usleep(1000000);
        }
	}

	void Client::run(const std::function<void(const std::string&)>& dataHandler) {
	    std::thread read(&Client::readLoop, this, dataHandler);
	    std::thread write(&Client::writeLoop, this);

	    //read.join();
	    write.join();

	    std::cout << "Closing client" << std::endl;
	}
}
