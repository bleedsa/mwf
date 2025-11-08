#!/bin/sh

X() {
	echo $@
	$@
}

cd 3rd/msgpack/
X mkdir -p build
cd build
X cmake -GNinja ..
X ninja
