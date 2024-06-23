#include "Path.h"

#include <stdexcept>

Path::Path(const std::vector<TileCoordinates> newPath) : currentStep(newPath.size() - 1), path(newPath)
{
	if (newPath.empty())
	{
		throw std::logic_error("Tried to create an empty Path object");
	}
}

Path::~Path()
{
	path.clear();
}

/**
 * Move current() to the next tile in the path, returning that tile's coordinates.
 * Calling this method on the last set of coordinates of the path will finish the path.
 * If the path is already finished before calling this method, this method returns an empty std::optional.
 */
std::optional<TileCoordinates> Path::next()
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
 * If the path is finished, this method will return an empty std::optional.
 */
std::optional<TileCoordinates> Path::current() const
{
	if (finished)
	{
		return {};
	}

	return path[currentStep];
}

/**
 * Return the last tile in the path (the 'destination'), even if the path has been finished.
 */
TileCoordinates Path::end() const
{
	return path.front();
}
