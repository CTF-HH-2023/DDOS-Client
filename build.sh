#!/bin/sh

WORKING_DIRECTORY=$(pwd)

CURL_VERSION='8.4.0'

set -exu

# https://github.com/moparisthebest/static-curl
lib_curl(){
  cd "${WORKING_DIRECTORY}/lib"

  if [ ! -f curl-${CURL_VERSION}.tar.gz ]; then

    wget https://curl.haxx.se/download/curl-${CURL_VERSION}.tar.gz https://curl.haxx.se/download/curl-${CURL_VERSION}.tar.gz.asc

  fi

  rm -rf "curl-${CURL_VERSION}/"
  tar xzf curl-${CURL_VERSION}.tar.gz

  cd curl-${CURL_VERSION}/

  export CC=musl-gcc

  LDFLAGS="-static" PKG_CONFIG="pkg-config --static" ./configure --disable-shared --enable-static --disable-ldap --enable-unix-sockets --without-ssl --disable-cookies --disable-basic-auth --disable-bearer-auth --disable-digest-auth --disable-kerberos-auth --disable-negotiate-auth --disable-aws --disable-dateparse --disable-doh --disable-ipv6 --disable-manual --disable-pthreads --disable-socketpair --disable-threaded-resolver --disable-tls-srp --disable-verbose --disable-versioned-symbols --enable-symbol-hiding --without-brotli --without-libpsl --without-zstd --without-zlib

  make -j4 V=1 LDFLAGS="-static -all-static"

  strip src/curl

  ls -lah src/curl
  file src/curl

  ldd src/curl && exit 1 || true

  ./src/curl -V

  ./src/curl -v http://www.moparisthebest.com/

  rm -rf "curl-${CURL_VERSION}.tar.gz" "curl-${CURL_VERSION}.tar.gz.asc"

  cd "${WORKING_DIRECTORY}"
}


if [ ! -d "${WORKING_DIRECTORY}/lib/curl-${CURL_VERSION}/" ]; then
    if [ ! -d "${WORKING_DIRECTORY}/lib/" ]; then
      mkdir "${WORKING_DIRECTORY}/lib"
    fi

    lib_curl
  fi

sudo apt-get -y install musl-tools

musl-gcc -o ddos ddos.c -I./lib/curl-8.4.0/include -L./lib/curl-8.4.0/lib/.libs -lcurl -static -static-libgcc

strip --strip-debug ddos

ls -lah ddos
file ddos

ldd ddos && exit 1 || true
