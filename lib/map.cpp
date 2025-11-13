#include <vector>

#include <map.h>
#include <M.h>

X Map::Tile::pack(msgpack::sbuffer &buf) -> V {
	msgpack::pack(buf, (S)ty);
}

Map::Map::Map(S x, S y) : tiles{M::M<Tile>(x, y)}, items{std::vector<Item>()} {}

X Map::Map::pack(msgpack::sbuffer &buf) -> V {
	X p = msgpack::packer<msgpack::sbuffer>(&buf);

	/* pack the tiles */
	S r = tiles.rows, c = tiles.cols;
	p.pack(r);
	p.pack(c);
	for (S i = 0; i < r*c; i++) {
		X x = &tiles.ptr[i];
		p.pack((S)x->ty);
	}

	/* pack the items */
	S z = items.size();
	p.pack(items.size());
	for (S i = 0; i < z; i++) {
		X x = &items[i];
		p.pack((S)x->ty);
	}
}
