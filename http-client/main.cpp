#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <print>
#include <array>
#include <iostream>

#include <cstdlib>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

using asio::ip::tcp;

int main(const int argc, const char* argv[])
{
	if (argc != 4)
	{
		std::println(stderr, "Usage: <adress> <port> <target> [version]");
		return EXIT_FAILURE;
	}

	const char* const address = argv[1];
	const char* const port = argv[2];
	const char* const target = argv[3];
	int version = (argc == 5 && !std::strcmp("1.0", argv[4])) ? 10 : 11;

	asio::io_context io_context;

	tcp::resolver resolver{io_context};
	beast::tcp_stream stream{io_context};

	tcp::resolver::results_type results = resolver.resolve(address, port);

	stream.connect(results);

	// Set up an HTTP GET request message
	http::request<http::string_body> req{http::verb::get, target, version};
	req.set(http::field::host, address);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	http::write(stream, req);

	// This buffer is used for reading and must be persisted
	beast::flat_buffer buffer;

	// Declare a container to hold the response
	http::response<http::dynamic_body> res;

	// Receive the HTTP response
	http::read(stream, buffer, res);

	// Write the message to standard out
	std::cout << res << std::endl;

	// Gracefully close the socket
	beast::error_code ec;
	stream.socket().shutdown(tcp::socket::shutdown_both, ec);

	// not_connected happens sometimes
	// so don't bother reporting it.
	if(ec && ec != beast::errc::not_connected)
		throw beast::system_error{ec};

	// If we get here then the connection is closed gracefully

	return EXIT_SUCCESS;
}
