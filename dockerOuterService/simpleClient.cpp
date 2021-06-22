#include <iostream>
#include <string>

#include <nghttp2/asio_http2_client.h>

using boost::asio::ip::tcp;

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::client;

#define ENV_INNER_SERVICE_DNS "DNS_INNER_SERVICE"

int main(int argc, char *argv[]) {
  boost::system::error_code ec;
  boost::asio::io_service io_service;

  const std::string target_url	= getenv(ENV_INNER_SERVICE_DNS);
  const std::string target_port	= "3000";
  const std::string full_url	= "http://"+target_url+"/"+target_port;

  
  session sess(io_service, target_url, target_port);

  sess.on_connect([&sess, &full_url](tcp::resolver::iterator endpoint_it) {
    boost::system::error_code ec;

    auto req = sess.submit(ec, "POST", full_url);
    //auto req = sess.submit(ec, "GET", full_url);

    req->on_response([](const response &res) {
      // print status code and response header fields.
      std::cerr << "HTTP/2 " << res.status_code() << std::endl;
      for (auto &kv : res.header()) {
        std::cerr << kv.first << ": " << kv.second.value << "\n";
      }
      std::cerr << std::endl;

      res.on_data([](const uint8_t *data, std::size_t len) {
        std::cerr.write(reinterpret_cast<const char *>(data), len);
        std::cerr << std::endl;
      });
    });

    req->on_close([&sess](uint32_t error_code) {
      // shutdown session after first request was done.
      sess.shutdown();
    });
  });

  sess.on_error([](const boost::system::error_code &ec) {
    std::cerr << "error: " << ec.message() << std::endl;
  });

  io_service.run();
}
