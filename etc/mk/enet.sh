#!/bin/sh

cd 3rd/enet
mkdir -p o
autoreconf -vfi
CPPFLAGS='-fPIE' ./configure --disable-shared --prefix=`pwd`/../../o 
make install
