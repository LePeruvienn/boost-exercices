#include <boost/asio.hpp>

#include <print>
#include <functional>

namespace asio = boost::asio;

void finished_waiting(const boost::system::error_code& e, asio::steady_timer& t,
                      const std::size_t total_wait_duration, std::size_t wait_duration, std::size_t step_duration)
{
	if (wait_duration < step_duration)
	{
		step_duration = wait_duration;
	}

	wait_duration -= step_duration;

	std::println("Finished waiting {} seconds : {}",  total_wait_duration - wait_duration, e.message());

	if (wait_duration == 0)
	{
		std::println("DONE! {}", e.message());
		return;
	}

	t.expires_at(t.expiry() + asio::chrono::seconds(step_duration));
	t.async_wait(std::bind(finished_waiting, asio::placeholders::error, std::ref(t), total_wait_duration, wait_duration, step_duration));
}

int main()
{
	asio::io_context io;

	const std::size_t wait_duration = 5;
	const std::size_t step_duration = 1;

	asio::steady_timer t{io, asio::chrono::seconds(step_duration)};

	std::println("Wating {} seconds async ...", wait_duration);

	t.async_wait(std::bind(finished_waiting, asio::placeholders::error, std::ref(t),
	                                         wait_duration, wait_duration, step_duration));

	io.run();

	return 0;
}

