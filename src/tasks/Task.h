#ifndef SRC_GAME_TASK_H_
#define SRC_GAME_TASK_H_

#include <string>

class Tile;
class District;
class Citizen;

namespace Tasks {

class Task {
private:
	bool deleteMe;
	Tile* pTile;
	std::string name;
	bool completed;
	int workRemaining;
protected:
	District* pDistrict;
	virtual void onCompletion() = 0;
public:
	Task(District*, Tile*, std::string, int);
	virtual ~Task();
	District* getDistrict() const { return pDistrict; }
	Tile* getTile() const { return pTile; }
	std::string getName() const { return name; }
	bool isCompleted() const { return completed; }
	int getWorkRemaining() const { return workRemaining; }
	bool citizenInRange(Citizen*);
	void workOn(Citizen*);
	void deleteTask() { deleteMe = true; }
	bool needsDeleting() const { return deleteMe; }
};

}

#endif /* SRC_GAME_TASK_H_ */
