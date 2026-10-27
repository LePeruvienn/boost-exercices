#include <boost/asio.hpp>

#include <print>
#include <array>
#include <iostream>

namespace asio = boost::asio;

using asio::ip::tcp;

int main(const int argc, const char* argv[])
{
	if (argc != 3)
	{
		std::println(stderr, "Usage: <host> <port>");
		return 1;
	}

	try
	{
		asio::io_context io_context;
		tcp::resolver resolver{io_context};

		tcp::resolver::results_type endpoints = resolver.resolve(argv[1], argv[2]);

		std::println("Starting connection at {} {} ...", argv[1], argv[2]);

		tcp::socket socket(io_context);
		asio::connect(socket, endpoints);

		std::println("Connected!");

		for(;;)
		{
			std::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(asio::buffer(buf), error);

			if (error == asio::error::eof)
			{
				std::println("Connection ended.");
				break;
			}
			else if (error)
			{
				throw boost::system::system_error(error); // Some other error.
			}

			std::cout.write(buf.data(), len);
			std::cout.flush();
		}
	}
	catch(const std::exception& e)
	{
		std::println(stderr, "ERROR: {}", e.what());
	}

	return 0;
}
