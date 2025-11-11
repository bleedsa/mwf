#include <vector>

#include <map.h>
#include <M.h>

X Map::Tile::pack() -> msgpack::sbuffer {
	msgpack::sbuffer buf;
	msgpack::pack(buf, (S)ty);
	return buf;
}

Map::Map::Map(S x, S y) : tiles{M::M<Tile>(x, y)}, items{std::vector<Item>()} {}
