#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "Entity.h"
#include <string>

class Path;
class Tile;

namespace Tasks {
class Task;
}

class Citizen : public Entity {
private:
	Tasks::Task* pCurrentTask;
public:
	Citizen(District*, const std::string);
	virtual ~Citizen();
	virtual void simulate();
	void move(int direction);
	void move(Tile* const moveToTile);
};

#endif /* CITIZEN_H_ */
