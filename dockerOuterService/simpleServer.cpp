#include <iostream>
#include <string>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include <nghttp2/asio_http2_server.h>

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[]) {
  boost::system::error_code ec;
  
  http2 server;

  server.handle("/", [](const request &req, const response &res) {
    res.write_head(200);
    res.end(exec("./resultClient"));
  });
  
  if (server.listen_and_serve(ec, "0.0.0.0", "3000")) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}
