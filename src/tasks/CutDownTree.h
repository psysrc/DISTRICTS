#ifndef SRC_TASKS_CUTDOWNTREE_H_
#define SRC_TASKS_CUTDOWNTREE_H_

#include <tasks/Task.h>

class District;
class Tile;

namespace Tasks
{

	class CutDownTree : public Task
	{
	public:
		CutDownTree(Tile *, District *);
		virtual ~CutDownTree();

	protected:
		virtual void onCompletion() override;
		District *pDistrict;
	};

}

#endif /* SRC_TASKS_CUTDOWNTREE_H_ */
