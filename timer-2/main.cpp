#include <boost/asio.hpp>

#include <print>
#include <vector>

namespace asio = boost::asio;

int main()
{
	asio::io_context io;

	std::vector<asio::steady_timer> timers;

	for (std::size_t i = 1; i < 6; ++i)
	{
		asio::steady_timer t{io, asio::chrono::seconds(i)};

		std::println("Wating {} seconds async ...", i);

		t.async_wait([i](const boost::system::error_code& e) {
			std::println("Finished waiting {} seconds : {}", i, e.message());
		});

		timers.push_back(std::move(t));
	}

	io.run();

	return 0;
}
