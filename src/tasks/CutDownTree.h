#ifndef SRC_TASKS_CUTDOWNTREE_H_
#define SRC_TASKS_CUTDOWNTREE_H_

#include <tasks/Task.h>

class District;
class Tile;

namespace Tasks {

class CutDownTree : public Task {
public:
	CutDownTree(District*, Tile*);
	virtual ~CutDownTree();
protected:
	virtual void onCompletion() override final;
};

}

#endif /* SRC_TASKS_CUTDOWNTREE_H_ */
