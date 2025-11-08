#!/bin/sh

X() {
	echo $@
	$@
}

cd 3rd/raylib
X mkdir -p build
cd build
X cmake -GNinja -DWITH_PIC=on ..
X ninja
