FROM ubuntu:18.04

RUN apt update && apt-get install g++ make binutils autoconf automake autotools-dev libtool pkg-config \
  zlib1g-dev libcunit1-dev libssl-dev libxml2-dev libev-dev libevent-dev libjansson-dev \
  libc-ares-dev libjemalloc-dev libsystemd-dev \
  cython python3-dev python-setuptools \
  nghttp2 \
  libboost-all-dev \
  wget -y


#nghttp && server
RUN wget https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.bz2
RUN tar -xvjf nghttp2-1.30.0.tar.bz2
RUN mv nghttp2-1.30.0 /nghttp

WORKDIR /nghttp

COPY ./simpleServer.cpp ./simpleServer.cpp
COPY ./index.html ./index.html



RUN ./configure --enable-asio-lib
RUN make && make install

#build server into resultServer file
RUN g++ -std=c++11 -I ./src/includes -I ./lib/includes simpleServer.cpp -o resultServer -lnghttp2_asio -lboost_system -lssl -lcrypto

#? magic
RUN ldconfig -v

#starting the server
EXPOSE 3000
ENTRYPOINT ./resultServer
