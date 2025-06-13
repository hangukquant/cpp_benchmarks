#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <iostream>
#include <string>
#include <fmt/core.h>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp_socket = net::ip::tcp::socket;

auto connect_websocket(
    net::io_context& ioc,
    ssl::context& ctx,
    const std::string& host,
    const std::string& port,
    const std::string& target
) {
    net::ip::tcp::resolver resolver(ioc);
    websocket::stream<ssl::stream<tcp_socket>> ws(ioc, ctx);

    auto const results = resolver.resolve(host, port);
    net::connect(ws.next_layer().next_layer(), results.begin(), results.end());
    ws.next_layer().handshake(ssl::stream_base::client);

    if(!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str())) {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        throw beast::system_error{ec};
    }

    ws.handshake(host, target);
    return ws;
}

int main() {
    fmt::print("hi\n");

    try {
        const std::string host = "stream.binance.com";
        const std::string port = "9443";
        const std::string target = "/ws/btcusdt@trade";

        net::io_context ioc;
        ssl::context ctx(ssl::context::tlsv12_client);
        ctx.set_default_verify_paths();

        auto ws = connect_websocket(ioc, ctx, host, port, target);

        std::cout << "Connected to Binance BTCUSDT trade stream. Printing messages:\n";
        for (;;) {
            beast::flat_buffer buffer;
            ws.read(buffer);
            std::cout << beast::make_printable(buffer.data()) << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}