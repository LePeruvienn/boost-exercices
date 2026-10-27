#include <boost/asio.hpp>

#include <boost/asio/ip/address.hpp>
#include <print>
#include <cstdint>

namespace asio = boost::asio;

using asio::ip::tcp;

asio::io_context io_context;

void end_connection(asio::steady_timer* timer, tcp::socket* socket, const boost::system::error_code&)
{
	std::println("DONE!");
	delete socket;
	delete timer;
}

void accept_connection(tcp::acceptor& acceptor);

void handle_connection(tcp::acceptor& acceptor, tcp::socket* socket, const boost::system::error_code&)
{
	const tcp::endpoint& remote_endpoint = socket->remote_endpoint();
	const asio::ip::address& remote_adress = remote_endpoint.address();

	std::println("Handling connection {} ...", remote_adress.to_string());

	static const std::string message{"Wating 5 seconds ...\n"};

	asio::async_write(*socket, asio::buffer(message), [](const boost::system::error_code&, std::size_t){});

	asio::steady_timer* timer = new asio::steady_timer(io_context, asio::chrono::seconds(5));
	timer->async_wait(std::bind(end_connection, timer, socket, asio::placeholders::error));

	accept_connection(acceptor);
}

void accept_connection(tcp::acceptor& acceptor)
{
	tcp::socket* socket = new tcp::socket(io_context);
	acceptor.async_accept(*socket, std::bind(handle_connection, std::ref(acceptor), socket, asio::placeholders::error));
}

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

		tcp::endpoint endpoint{adress, port};
		tcp::acceptor acceptor(io_context, endpoint);

		std::println("Liseting at {} port {}", adress.to_string(), port);

		accept_connection(acceptor);
		io_context.run();

	}
	catch (const std::exception& e)
	{
		std::println("ERROR: {}", e.what());
	}

	return 0;
}
