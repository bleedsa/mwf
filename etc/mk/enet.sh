#!/bin/sh

cd 3rd/enet
mkdir o
./configure --enable-static --prefix=`pwd`/o
make install
