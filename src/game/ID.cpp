#include "game/ID.h"

// Returns a new unique ID for an Entity
ID_t uniqueEntityID()
{
	static ID_t nextEntityID = NullID + 1;
	return nextEntityID++;
}
