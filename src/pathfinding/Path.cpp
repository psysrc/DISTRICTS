#include "Path.h"

#include <stdexcept>

Path::Path(const std::vector<DeprecatedTile *> newPath) : currentStep(newPath.size() - 1), path(newPath)
{
	if (newPath.empty())
		throw std::logic_error("Tried to create an empty Path object");
}

Path::~Path()
{
	path.clear();
}

/**
 * Move current() to the next tile in the path, returning that tile.
 * Calling this method on the last tile of the path will finish the path.
 * If the path is finished, this method and current() will return nullptr.
 */
DeprecatedTile *Path::next()
{
	if (currentStep == 0)
	{
		finished = true;
	}
	else
	{
		currentStep--;
	}

	return current();
}

/**
 * Returns the current tile along the path.
 * If the path is finished, this method and next() will return nullptr.
 */
DeprecatedTile *Path::current() const
{
	if (finished)
		return nullptr;

	return path[currentStep];
}

/**
 * Always returns the last tile in the path (the 'destination'), even if the path has been finished.
 */
DeprecatedTile *Path::end() const
{
	return path.front();
}
