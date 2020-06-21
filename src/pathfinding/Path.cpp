#include "Path.h"

Path::Path(const std::vector<Tile*> newPath) : currentStep(newPath.size()), path(newPath) {

}

Path::~Path() {
	path.clear();
}

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

Tile* Path::current() {
	if (finished || currentStep >= path.size())
		return nullptr;

	return path[currentStep];
}