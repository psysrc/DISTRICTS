#ifndef SRC_TASKS_BUILDBRIDGE_H_
#define SRC_TASKS_BUILDBRIDGE_H_

#include <tasks/Task.h>

class DeprecatedTile;

namespace Tasks
{

	class BuildBridge : public Task
	{
	public:
		BuildBridge(DeprecatedTile *);
		virtual ~BuildBridge();

	protected:
		virtual void onCompletion(District*) override;
	};

}

#endif /* SRC_TASKS_BUILDBRIDGE_H_ */
