#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <exception>

#define DEBUG true

#define DISTRICT_SIZE 32

#define COLOUR_CITIZEN 1
#define COLOUR_WATER 2
#define COLOUR_PLAINS 3
#define COLOUR_STONE 4
#define COLOUR_UNKNOWN 5

enum TileProperty {
	NullProperty,
	Plains,
	Water,
	Stone,
	Tree
};

class UninitialisedObjectException : public std::exception {
	virtual const char* what() const noexcept
	{
		return "Trying to use an uninitialised object";
	}
};

#endif /* CONSTANTS_H_ */
