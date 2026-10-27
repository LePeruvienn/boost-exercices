#include "printer.h"

#include <boost/asio.hpp>

namespace asio = boost::asio;

int main()
{
	asio::io_context io;

	Printer p1{io, asio::chrono::seconds{5}, asio::chrono::seconds{1}};
	Printer p2{io, asio::chrono::seconds{3}, asio::chrono::milliseconds{500}};

	io.run();

	return 0;
}

