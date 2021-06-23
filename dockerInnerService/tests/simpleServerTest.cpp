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
    std::string data_str;
    bool on_data_success;
    req.on_data([&data_str, &on_data_success](const uint8_t *data, std::size_t len){
      //std::cerr<<"Hello: ";
      //std::cout<<"Hello: ";
      std::cerr.write(reinterpret_cast<const char *>(data), len);
      //std::cerr<<"hello. ";
      //std::cout<<"hello. ";
      char *temp = new char[len+1];
      strncpy(temp,reinterpret_cast<const char*>(data),len);
      temp[len]='\0';
      std::cerr<<temp;
      //data_str.append(temp);//data_str = std::string(temp); literally crashes the whole server

      Document d;
      d.Parse(temp);

      if (!d.HasParseError() && d.HasMember("testRequest")){
  	  data_str= std::string("{\"testResponce\":\"success\"}"); 
//	  data_str.append("{\"testResponce\":\"success\"}"); //crashes
          on_data_success=true;
	  std::cout<<"inside if";
      }
      //char *temp = new char[len+1];
      //strncpy(temp,reinterpret_cast<const char*>(data),len);
      //temp[len]='/0';
      //std::cout<<temp;


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
    std::cout<<on_data_success;
    if(on_data_success){
      std::cout<<"on_data_success part";
      res.write_head(200);
      res.end(data_str.c_str());
    }else{
      std::cout<<"on_data_no_success";
      res.write_head(500);
      res.end("no json provided");
    }
  });

  if (server.listen_and_serve(ec, "0.0.0.0", "3001")) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}

