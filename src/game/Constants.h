#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <exception>

#define DEBUG true
#define BIOME_GEN true
#define TREE_GEN true

#define DISTRICT_SIZE 32

#define COLOUR_UNKNOWN		1
#define COLOUR_WATER		2
#define COLOUR_PLAINS		3
#define COLOUR_STONE		4
#define COLOUR_HIGHLIGHTED	5
#define COLOUR_BRIDGE		6

#define NorthWest	0
#define North		1
#define NorthEast	2
#define West		3
#define East		4
#define SouthWest	5
#define South		6
#define SouthEast	7

namespace TileProperty {

enum TileProperty {
	NullProperty,
	Plains,
	Water,
	Stone,
	Bridge,
};

}

class UninitialisedObjectException : public std::exception {
	virtual const char* what() const noexcept
	{
		return "Trying to use an uninitialised object";
	}
};

#endif /* CONSTANTS_H_ */
