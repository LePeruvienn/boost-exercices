#include "printer.h"

#include <functional>
#include <print>

Printer::Printer(asio::io_context& io, asio::chrono::steady_clock::duration duration,  asio::chrono::steady_clock::duration step) :
	m_io(io),
	m_timer(m_io, step), 
	m_total_duration(duration),
	m_step_duration(step),
	m_time_left(duration)
{
	std::println("Wating {} seconds with {} seconds step. ...", asio::chrono::duration<double>(duration), asio::chrono::duration<double>(step));
	m_timer.async_wait(std::bind(&Printer::print, this));
}

Printer::~Printer()
{
	m_timer.cancel();
}

void Printer::print()
{
	if (m_time_left < m_step_duration)
	{
		m_time_left = m_time_left.zero();
	}
	else
	{
		m_time_left -= m_step_duration;
	}

	if (m_time_left == m_time_left.zero())
	{
		std::println("Done waiting {} seconds.", asio::chrono::duration<double>(m_total_duration));
		return;
	}

	std::println("Finished waiting {} seconds.", asio::chrono::duration<double>(m_total_duration - m_time_left));

	m_timer.expires_at(m_timer.expiry() + m_step_duration);
	m_timer.async_wait(std::bind(&Printer::print, this));
}
