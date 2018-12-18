#include "Client.hpp"
#include "../../SAMOVAR/Main.cpp"
#include <iterator>
#include <iostream>

typedef CraftWorld::Utility::Vector3D<int> player_coord;

namespace CraftWorld {
	Client::Client(const std::string& host, const int& port, int ID) : socket_(
		[&]() {
                    // Initialize ID
                    Client::ID = ID;

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
	    while(true)
        {
	        // TODO: put client game decision making here and write it to the server, remove the break when done
                // Get player coordinates
                playercoord = getPlayerCoord(map, player, ID);
                

                // Randomly choose function:
                  switch(rand() % 4) {
                    case 0: playercoord = moveNorth(); break;
                    case 1: playercoord = moveEast(); break;
                    case 2: playercoord = moveSouth(); break;
                    case 3: playercoord = moveWest(); break;
                  }

	        // Just wrote something to the server, wait 10 milliseconds in order to avoid server overloading
            boost::this_thread::sleep( boost::posix_time::millisec(10));
	        break;
        }
	}

	void Client::run(const std::function<void(const std::string&)>& dataHandler) {
        boost::thread_group threads;

        threads.create_thread(boost::bind(&Client::readLoop, this, dataHandler));
        threads.create_thread(boost::bind(&Client::writeLoop, this));

        threads.join_all();
	}
}
