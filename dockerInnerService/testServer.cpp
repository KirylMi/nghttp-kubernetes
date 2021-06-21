#include <nghttp2/asio_http2_server.h>
#include <iostream>
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

int main(int argc, char *argv[]) {
  boost::system::error_code ec;
  http2 server;

  std::string style_css = "h1 { color: green; }";

  server.handle("/", [&style_css](const request &req, const response &res) {
    boost::system::error_code ec;
    auto push = res.push(ec, "GET", "/style.css");
    push->write_head(200);
    push->end(style_css);

    res.write_head(200);
    res.end(R"(
<!DOCTYPE html><html lang="en">
<title>HTTP/2 FTW</title><body>
<link href="/style.css" rel="stylesheet" type="text/css">
<h1>This should be green</h1>
</body></html>
)");
  });

  server.handle("/style.css",
                [&style_css](const request &req, const response &res) {
    res.write_head(200);
    res.end(style_css);
  });

  if (server.listen_and_serve(ec, "localhost", "3001")) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}

