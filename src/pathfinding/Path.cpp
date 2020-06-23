#include "Path.h"

Path::Path(const std::vector<Tile*> newPath) : currentStep(newPath.size()), path(newPath) {

}

Path::~Path() {
	path.clear();
}

/**
 * Move current() to the next tile in the path, returning that tile.
 * If the path has been finished, this method and current() will both return nullptr.
 */
Tile* Path::next() {
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
 * Returns nullptr if next() has not been called on this path yet.
 * If the path has been finished, this method and next() will both return nullptr.
 */
Tile* Path::current() const {
	if (finished || currentStep >= path.size())
		return nullptr;

	return path[currentStep];
}

/**
 * Returns the last tile in the path, even if the path has been finished.
 * If the path is empty, this method returns nullptr.
 */
Tile* Path::end() const {
	if (path.empty())
		return nullptr;
	else
		return path.front();
}