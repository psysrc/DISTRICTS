#ifndef DISTRICT_H_
#define DISTRICT_H_

#include "Constants.h"
#include "Tile.h"
#include "Citizen.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

#define DISTRICT_SIZE 10

class District {
private:
	Tile** tiles;
	std::vector<Citizen*> citizens;
public:
	District();
	~District();
	void simulate();
};

#endif /* DISTRICT_H_ */
