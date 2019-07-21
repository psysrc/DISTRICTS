#ifndef DISTRICT_H_
#define DISTRICT_H_

#include "Tile.h"
#include "Citizen.h"

#define DISTRICT_SIZE 10

class District {
private:
	Tile** tiles;
	Citizen* citizens[];
public:
	District();
	~District();
	void simulate();
};

#endif /* DISTRICT_H_ */
