#ifndef SRC_TASKS_CUTDOWNTREE_H_
#define SRC_TASKS_CUTDOWNTREE_H_

#include <tasks/Task.h>

class District;
class DeprecatedTile;
class Entity;

namespace Tasks
{

	class CutDownTree : public DeprecatedTask
	{
	public:
		CutDownTree(DeprecatedTile *, District *, Entity *);
		virtual ~CutDownTree();

	protected:
		virtual void onCompletion(District*) override;
		District *pDistrict;
		Entity* tree;
	};

}

#endif /* SRC_TASKS_CUTDOWNTREE_H_ */
