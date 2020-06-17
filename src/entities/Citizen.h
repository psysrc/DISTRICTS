#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "Entity.h"
#include <memory>
#include <string>

class Path;
class Tile;

namespace Tasks {
class Task;
}

class Citizen : public Entity {
private:
	std::unique_ptr<Path> upCurrentPath;
	Tasks::Task* pCurrentTask;
public:
	Citizen(District*, const std::string);
	virtual ~Citizen();
	virtual void simulate();
	void move(int direction);
	void move(Tile* const moveToTile);
};

#endif /* CITIZEN_H_ */
