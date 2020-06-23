#ifndef SRC_GAME_TASK_H_
#define SRC_GAME_TASK_H_

#include <string>

class Tile;

namespace Tasks {

class Task {
private:
	Tile* pTile;
	std::string name;
	bool completed;
	int workRemaining;
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
