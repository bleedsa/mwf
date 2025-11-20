#!/bin/sh

R="`pwd`"
rm -rf o

cd 3rd/enet; {
	make clean
}; cd "$R"

rm -rf 3rd/msgpack-c/build
rm -rf 3rd/sdl3/build
