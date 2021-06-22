#include <iostream>

#include <nghttp2/asio_http2_server.h>

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

using namespace rapidjson;

int main(int argc, char *argv[]) {
  boost::system::error_code ec;
  http2 server;

  // 1. Parse a JSON string into DOM.
  //const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
  //Document d;
  //d.Parse(json);
 
  // 2. Modify it by DOM.
  //Value& s = d["stars"];
  //s.SetInt(s.GetInt() + 1);
 
  // 3. Stringify the DOM
  //StringBuffer buffer;
  //Writer<StringBuffer> writer(buffer);
  //d.Accept(writer);

  server.handle("/", [](const request &req, const response &res) {
    req.on_data([&res](const uint8_t *data, std::size_t len) {
      //Document d;
      std::cerr.write(reinterpret_cast<const char *>(data), len);
      //STRCPY with new char* [len] etc...
      //monstrosity
      //char *cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(data));
      //d.Parse(cptr);
      //std::cerr<<"data received: "<<data;
      //if(d.HasMember("testRequest")){
      //  res.write_head(200);
      //  res.end("{\"testResponce\":\"success\"}");
      //}      
    });
    //res.write_head(500);
    res.write_head(200);
    res.end("something is wrong with the request body");
  });

  if (server.listen_and_serve(ec, "0.0.0.0", "3000")) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}
