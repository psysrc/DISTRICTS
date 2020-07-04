#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <exception>

#define BIOME_GEN true
#define TREE_GEN true

#define COLOUR_UNKNOWN		1
#define COLOUR_WATER		2
#define COLOUR_PLAINS		3
#define COLOUR_STONE		4
#define COLOUR_HIGHLIGHTED	5
#define COLOUR_BRIDGE		6

namespace TileProperty {

enum TileProperty {
	Plains,
	Water,
	Stone,
	Bridge,
};

}

#endif /* CONSTANTS_H_ */
