#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <exception>

#define DEBUG true

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
