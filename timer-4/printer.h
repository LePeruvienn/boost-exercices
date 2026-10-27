#ifndef PRINTER_H
#define PRINTER_H

#include <boost/asio.hpp>

namespace asio = boost::asio;

class Printer
{
public:
	Printer(asio::io_context& io, asio::chrono::steady_clock::duration duration,  asio::chrono::steady_clock::duration step);
	~Printer();

private:
	asio::io_context& m_io;
	asio::steady_timer m_timer;

	asio::chrono::steady_clock::duration m_total_duration;
	asio::chrono::steady_clock::duration m_step_duration;
	asio::chrono::steady_clock::duration m_time_left;

	void print();
};

#endif // PRINTER_H


