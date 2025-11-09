#include <vector>

#include <map.h>
#include <M.h>

Map::Map::Map(S x, S y) : tiles{M::M<Tile>(x, y)}, items{std::vector<Item>()} {}
