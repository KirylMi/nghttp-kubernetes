FROM ubuntu:18.04

RUN apt update && apt-get install g++ make binutils autoconf automake autotools-dev libtool pkg-config \
  libcunit1-dev libxml2-dev libev-dev libevent-dev libjansson-dev \
  libc-ares-dev libjemalloc-dev libsystemd-dev \
  nghttp2 \
  wget -y

#nghttp
RUN wget https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.bz2
RUN tar -xvjf nghttp2-1.30.0.tar.bz2
RUN mv nghttp2-1.30.0 /nghttp

WORKDIR /nghttp

RUN ./configure --enable-asio-lib
RUN make && make install

#? magic
RUN ldconfig -v

#CURL ###maybe add temp/dir to all of the dependencies

##zlib 1.2.11
RUN wget http://www.zlib.net/zlib-1.2.11.tar.gz
RUN tar -xvzf zlib-1.2.11.tar.gz
RUN mv zlib-1.2.11 /zlib
WORKDIR /zlib
RUN ./configure
RUN make && make install
RUN ldconfig -v

##openssl 1.1.1
RUN wget https://www.openssl.org/source/openssl-1.1.1.tar.gz 
RUN tar -zxf openssl-1.1.1.tar.gz 
RUN mv openssl-1.1.1 /openSSL
WORKDIR /openSSL
RUN ./config
RUN make && make install
RUN rm /usr/bin/openssl
RUN ln -s /usr/local/bin/openssl /usr/bin/openssl
RUN ldconfig

##curl itself 7.58.0
RUN wget http://curl.haxx.se/download/curl-7.58.0.tar.bz2 --no-check-certificate
RUN tar -xvjf curl-7.58.0.tar.bz2
RUN mv curl-7.58.0 /curl
WORKDIR /curl
RUN ./configure --with-nghttp2=/usr/local --with-ssl
RUN make
RUN make install
RUN ldconfig

ENTRYPOINT ["curl"]
CMD ["--help"]
