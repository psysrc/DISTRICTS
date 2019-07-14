#ifndef DISTRICT_H_
#define DISTRICT_H_

#include "Tile.h"

#define DISTRICT_SIZE 10

class District {
private:
	Tile** tiles;
public:
	District();
	~District();
};

#endif /* DISTRICT_H_ */
