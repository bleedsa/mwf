#!/bin/sh

cd 3rd/enet
mkdir -p o
CPPFLAGS='-fPIE' ./configure --enable-static --prefix=`pwd`/o 
make install
