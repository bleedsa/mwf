#!/bin/sh

X() {
	echo $@
	$@
}

cd 3rd/msgpack/
X mkdir -p build
X cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -GNinja
X cmake --build build --config Release
X cmake --install build --prefix ../../o/
