#ifndef SRC_GAME_TASK_H_
#define SRC_GAME_TASK_H_

#include <string>
#include "game/ID.h"

class DeprecatedTile;
class District;

namespace Tasks
{

	class DeprecatedTask
	{
	public:
		DeprecatedTask(DeprecatedTile *, std::string, int);
		virtual ~DeprecatedTask();
		ID_t getID() const;
		DeprecatedTile *getTile() const;
		std::string getName() const;
		bool isCompleted() const;
		int getWorkRemaining() const;
		void workOn(District*);

	protected:
		virtual void onCompletion(District*) = 0;

	private:
		const ID_t id;
		DeprecatedTile *pTile;
		std::string name;
		bool completed;
		int workRemaining;
	};

}

#endif /* SRC_GAME_TASK_H_ */
