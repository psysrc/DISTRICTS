#ifndef SRC_TASKS_BUILDBRIDGE_H_
#define SRC_TASKS_BUILDBRIDGE_H_

#include <tasks/Task.h>

class District;
class Tile;

namespace Tasks {

class BuildBridge : public Task {
public:
	BuildBridge(District*, Tile*);
	virtual ~BuildBridge();
protected:
	virtual void onCompletion() override;
};

}

#endif /* SRC_TASKS_BUILDBRIDGE_H_ */
