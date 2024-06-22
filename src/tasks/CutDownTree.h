#ifndef SRC_TASKS_CUTDOWNTREE_H_
#define SRC_TASKS_CUTDOWNTREE_H_

#include <tasks/Task.h>

class District;
class DeprecatedTile;

namespace Tasks
{

	class CutDownTree : public Task
	{
	public:
		CutDownTree(DeprecatedTile *, District *);
		virtual ~CutDownTree();

	protected:
		virtual void onCompletion(District*) override;
		District *pDistrict;
	};

}

#endif /* SRC_TASKS_CUTDOWNTREE_H_ */
