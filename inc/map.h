#ifndef __MWF_MAP_H__
#define __MWF_MAP_H__

#include <u.h>
#include <M.h>
#include <item.h>
#include <vector>

namespace map {
	/* the type of a tile */
	enum TileTy {
		EMPTY,
		DIRT,
	};

	/* a tile in the map */
	struct Tile {
		TileTy ty;

		inl Tile(TileTy ty) : ty{ty} {}
	};

	/* a game map */
	struct Map {
		M::M<Tile> tiles;
		std::vector<Item> items;
	};
}

#endif
