#ifndef __MWF_MAP_H__
#define __MWF_MAP_H__

#include <msgpack.hpp>
#include <vector>

#include <u.h>
#include <M.h>
#include <item.h>

namespace Map {
	/* the type of a tile */
	enum TileTy {
		EMPTY,
		DIRT,
	};

	/* a tile in the map */
	struct Tile {
		TileTy ty;

		inl Tile() : ty{EMPTY} {}
		inl Tile(TileTy ty) : ty{ty} {}

		V pack(msgpack::sbuffer &buf);
	};

	/* a game map */
	struct Map {
		M::M<Tile> tiles;
		std::vector<Item> items;

		Map(S x, S y);
		inl ~Map() {}
		inl X at(S x, S y) -> Tile* {
			return tiles.at(x, y);
		}

		V pack(msgpack::sbuffer &buf);
	};
}

#endif
