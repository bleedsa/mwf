#!/bin/sh

cd 3rd/enet
mkdir o
CPPFLAGS='-fPIE' ./configure --enable-static --prefix=`pwd`/o 
make install
