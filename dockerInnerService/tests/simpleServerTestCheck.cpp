#include <iostream>
#include <string>

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
    std::string data_str;
    bool on_data_success = false;
    req.on_data([&data_str, &on_data_success](const uint8_t *data, std::size_t len){
      std::cerr.write(reinterpret_cast<const char *>(data), len);
      char *temp = new char[len+1];
      strncpy(temp,reinterpret_cast<const char*>(data),len);
      temp[len]='\0';

      Document d;
      d.Parse(temp);

      if (!d.HasParseError() && d.HasMember("testRequest")){
  	  data_str= std::string("{\"testResponce\":\"success\"}"); 
          on_data_success=1;
	  std::cout<<"inside if: "<<on_data_success<<"."<<std::endl; // returns "inside if: 0." wtf
      }      
    });
    std::cout<<"after if: "<<on_data_success<<"."<<std::endl;
    if(on_data_success){
      std::cout<<"on_data_success part";
      res.write_head(200);
      res.end(data_str.c_str());
    }else{
      std::cout<<"on_data_no_success";
      res.write_head(500);
      res.end("no json provided" + data_str);
    }
  });


  if (server.listen_and_serve(ec, "0.0.0.0", "3001")) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}

