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

  server.handle("/", [](const request &req, const response &res) {
    req.on_data([&res](const uint8_t *data, std::size_t len){
        //thogh logically if len==0 on_data shouldn't be invoked (imho), it's invoked anyway
        if(!len){ 
          res.write_head(500);
          res.end("empty request");
        }
        //after many tests, std::string still somehow crashes the whole server. So usual chars are used
	char* temp = new char[len+1];
      	strncpy(temp,reinterpret_cast<const char*>(data),len);
      	temp[len]='\0';
      	std::cout<<"ON DATA: "<<temp<<std::endl;        

      	Document d;
      	d.Parse(temp);

	if (!d.HasParseError() && d.HasMember("testRequest")){
          res.write_head(200);
	  res.end("{\"testResponce\":\"success\"}");
	}
	else{
          res.write_head(500);
	  res.end("something is wrong with json, or testRequest isn't present");
	}
    });
  });

  if (server.listen_and_serve(ec, "0.0.0.0", "3001")) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}

