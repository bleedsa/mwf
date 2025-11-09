#!/bin/sh

R="`pwd`"
rm -rf o

cd 3rd/enet; {
	make clean
}; cd "$R"

rm -rf 3rd/raylib/build
rm -rf 3rd/msgpack-c/build
