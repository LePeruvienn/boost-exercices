#include <boost/asio.hpp>

#include <boost/asio/ip/address.hpp>
#include <print>
#include <cstdint>

namespace asio = boost::asio;

using asio::ip::tcp;

const std::string message{"Hello"};

int main(const int argc, const char* argv[])
{
	if(argc != 3)
	{
		std::println("Usage: <adress> <port>");
		return 1;
	}

	try
	{
		const asio::ip::address adress = asio::ip::make_address(argv[1]);
		const std::uint16_t port = static_cast<std::uint16_t>(std::atoi(argv[2]));

		asio::io_context io_context;

		tcp::endpoint endpoint{adress, port};
		tcp::acceptor acceptor(io_context, endpoint);

		std::println("Liseting at {} port {}", adress.to_string(), port);

		tcp::socket socket(io_context);

		acceptor.accept(socket);

		boost::system::error_code ignored_error;

		asio::write(socket, asio::buffer(message), ignored_error);
	}
	catch (const std::exception& e)
	{
		std::println("ERROR: {}", e.what());
	}

	return 0;
}
