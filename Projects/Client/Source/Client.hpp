#pragma once

#include <functional>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Client {
			tcp::socket socket;

		public:
			Client(const std::string& host, const int& port);

			void run(const std::function<void(const std::string&)>& dataHandler);
	};
}
