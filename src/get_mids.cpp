#include "httplib.h"
#include <iostream>

int main() {
    httplib::Client cli("https://api.binance.com");
    auto res = cli.Get("/api/v3/midPrice");
    if (res) {
        std::cout << res->status << "\n" << res->body << std::endl;
    } else {
        std::cerr << "Request failed" << std::endl;
        return 1;
    }
    return 0;
}
