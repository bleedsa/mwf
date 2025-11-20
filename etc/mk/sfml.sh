cd 3rd/sfml
cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON
cmake --build build --config Release
cmake --install build --prefix ../../o/
