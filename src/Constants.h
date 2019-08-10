#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <exception>

#define DEBUG true

#define DISTRICT_SIZE 32

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
