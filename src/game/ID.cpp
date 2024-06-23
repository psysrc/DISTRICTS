#include "game/ID.h"

// Returns a new unique ID for an Entity
ID_t uniqueEntityID()
{
	static ID_t nextEntityID = NullID + 1;
	return nextEntityID++;
}

// Returns a new unique ID for a DeprecatedTask
ID_t uniqueDeprecatedTaskID()
{
	static ID_t nextTaskID = NullID + 1;
	return nextTaskID++;
}
