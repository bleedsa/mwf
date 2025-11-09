#!/bin/sh

out="`pwd`/o"
cd 3rd/enet
autoreconf -vfi
CPPFLAGS='-fPIE' ./configure --enable-static --disable-shared \
	--prefix="$out" --libdir "$out/lib"
make install
