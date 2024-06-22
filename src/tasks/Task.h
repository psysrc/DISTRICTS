#ifndef SRC_GAME_TASK_H_
#define SRC_GAME_TASK_H_

#include <string>
#include "game/ID.h"

class Tile;

namespace Tasks
{

	class Task
	{
	public:
		Task(Tile *, std::string, int);
		virtual ~Task();
		ID_t getID() const;
		Tile *getTile() const;
		std::string getName() const;
		bool isCompleted() const;
		int getWorkRemaining() const;
		void workOn();

	protected:
		virtual void onCompletion() = 0;

	private:
		const ID_t id;
		Tile *pTile;
		std::string name;
		bool completed;
		int workRemaining;
	};

}

#endif /* SRC_GAME_TASK_H_ */
