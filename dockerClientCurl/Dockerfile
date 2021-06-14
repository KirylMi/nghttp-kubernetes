FROM ubuntu:18.04

RUN apt update && apt-get install g++ make binutils autoconf automake autotools-dev libtool pkg-config \
  libcunit1-dev libxml2-dev libev-dev libevent-dev libjansson-dev \
  libc-ares-dev libjemalloc-dev libsystemd-dev \
  nghttp2 \
  wget -y

#nghttp
RUN wget https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.bz2 && \
 tar -xvjf nghttp2-1.30.0.tar.bz2 && \
 mv nghttp2-1.30.0 /nghttp

WORKDIR /nghttp

RUN ./configure --enable-asio-lib && \
  make && make install && \
  ldconfig -v

#CURL ###maybe add temp/dir to all of the dependencies

##zlib 1.2.11
RUN wget http://www.zlib.net/zlib-1.2.11.tar.gz && \
  tar -xvzf zlib-1.2.11.tar.gz && \
  mv zlib-1.2.11 /zlib

WORKDIR /zlib

RUN ./configure && \ 
  make && make install && \
  ldconfig -v

##openssl 1.1.1
RUN wget https://www.openssl.org/source/openssl-1.1.1.tar.gz && \
  tar -zxf openssl-1.1.1.tar.gz && \
  mv openssl-1.1.1 /openSSL

WORKDIR /openSSL

RUN ./config && \ 
  make && make install && \
  #changing version via symbol link
  rm /usr/bin/openssl && \
  ln -s /usr/local/bin/openssl /usr/bin/openssl && \
  ldconfig

##curl itself 7.58.0
RUN wget http://curl.haxx.se/download/curl-7.58.0.tar.bz2 --no-check-certificate && \
  tar -xvjf curl-7.58.0.tar.bz2 && \
  mv curl-7.58.0 /curl

WORKDIR /curl

RUN ./configure --with-nghttp2=/usr/local --with-ssl && \ 
  make && make install && \
  ldconfig

#ENTRYPOINT ["curl"]
#CMD ["--help"]
