#include <boost/asio.hpp>

#include <print>

namespace asio = boost::asio;

int main()
{
	asio::io_context io;

	asio::steady_timer t{io, asio::chrono::seconds(5)};

	std::println("Wating 5 seconds ...");

	t.wait();

	std::println("Done !");

	return 0;
}
