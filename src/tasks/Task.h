#ifndef SRC_GAME_TASK_H_
#define SRC_GAME_TASK_H_

#include <string>

class Tile;

typedef unsigned int TaskID_t;

namespace Tasks {

class Task {
private:
	const TaskID_t id;
	Tile* pTile;
	std::string name;
	bool completed;
	int workRemaining;
	static TaskID_t uniqueTaskID();
protected:
	virtual void onCompletion() = 0;
public:
	Task(Tile*, std::string, int);
	virtual ~Task();
	Tile* getTile() const { return pTile; }
	std::string getName() const { return name; }
	bool isCompleted() const { return completed; }
	int getWorkRemaining() const { return workRemaining; }
	void workOn();
};

}

#endif /* SRC_GAME_TASK_H_ */
