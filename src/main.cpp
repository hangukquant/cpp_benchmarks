#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <boost/asio/ssl/context.hpp>

#include <iostream>
#include <functional>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;

void on_message(client* c, websocketpp::connection_hdl, client::message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
}

void on_open(client*, websocketpp::connection_hdl) {
    std::cout << "Connected" << std::endl;
}

void on_fail(client*, websocketpp::connection_hdl) {
    std::cout << "Connection Failed" << std::endl;
}

void on_close(client*, websocketpp::connection_hdl) {
    std::cout << "Connection Closed" << std::endl;
}

int main() {
    client c;

    try {
        c.set_access_channels(websocketpp::log::alevel::all);
        c.set_error_channels(websocketpp::log::elevel::all);

        c.init_asio();

        c.set_message_handler(std::bind(&on_message, &c, std::placeholders::_1, std::placeholders::_2));
        c.set_open_handler(std::bind(&on_open, &c, std::placeholders::_1));
        c.set_fail_handler(std::bind(&on_fail, &c, std::placeholders::_1));
        c.set_close_handler(std::bind(&on_close, &c, std::placeholders::_1));
        c.set_tls_init_handler([](websocketpp::connection_hdl){
            auto ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12_client);
            ctx->set_default_verify_paths();
            ctx->set_verify_mode(boost::asio::ssl::verify_none);
            return ctx;
        });

        websocketpp::lib::error_code ec;
        auto con = c.get_connection("wss://stream.binance.com:9443/ws/btcusdt@trade", ec);
        if (ec) {
            std::cout << "Connection init error: " << ec.message() << std::endl;
            return 1;
        }

        c.connect(con);
        c.run();
    } catch(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
