FROM ubuntu:18.04

RUN apt update && apt-get install g++ make binutils autoconf automake autotools-dev libtool pkg-config \
  zlib1g-dev libcunit1-dev libssl-dev libxml2-dev libev-dev libevent-dev libjansson-dev \
  libc-ares-dev libjemalloc-dev libsystemd-dev \
  cython python3-dev python-setuptools \
  nghttp2 \
  libboost-all-dev \
  wget -y


#nghttp
RUN wget https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.bz2 && \
  tar -xjf nghttp2-1.30.0.tar.bz2 && \
  mv nghttp2-1.30.0 /nghttp && \
    wget https://github.com/Tencent/rapidjson/archive/refs/tags/v1.1.0.tar.gz && \
  tar -xzf v1.1.0.tar.gz && \
  mv rapidjson-1.1.0 /nghttp/rapidjson

WORKDIR /nghttp

#compiling server
RUN ./configure -q -C --enable-asio-lib && \
  make -j 2 && make install

COPY ./simpleServer.cpp ./simpleServer.cpp

#build server into resultServer file
RUN g++ -std=c++11 -I ./src/includes -I ./lib/includes -I ./rapidjson/include/rapidjson simpleServer.cpp -o resultServer -lnghttp2_asio -lboost_system -lssl -lcrypto && \
ldconfig -v

#starting the server
EXPOSE 3000
ENTRYPOINT ./resultServer
