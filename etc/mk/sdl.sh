#!/bin/sh

cd 3rd/sdl3/
cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release -DSDL_STATIC=ON
cmake --build build --config Release
cmake --install build --prefix ../../o/
ln -s ../../o/{lib64/libSDL3.a,lib/libSDL3.a}
echo done
