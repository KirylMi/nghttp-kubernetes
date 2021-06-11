FROM ubuntu:18.04

RUN apt update && apt-get install g++ make binutils autoconf automake autotools-dev libtool pkg-config \
  libcunit1-dev libxml2-dev libev-dev libevent-dev libjansson-dev \
  libc-ares-dev libjemalloc-dev libsystemd-dev \
  nghttp2 \
  wget -y && rm -rf /var/lib/apt/lists/* && \
  wget https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.bz2 && \
  tar -xvjf nghttp2-1.30.0.tar.bz2 && \
  mv nghttp2-1.30.0 /nghttp && \
  /nghttp/configure --enable-asio-lib && make && make install && \
  ldconfig -v

#nghttp
#RUN wget https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.bz2 && \
#  tar -xvjf nghttp2-1.30.0.tar.bz2 && \
#  mv nghttp2-1.30.0 /nghttp

#WORKDIR /nghttp

#RUN ./configure --enable-asio-lib && make && make install && yum -y clean all

#? magic
RUN ldconfig -v

ENTRYPOINT ["nghttp"]
CMD ["--help"]
