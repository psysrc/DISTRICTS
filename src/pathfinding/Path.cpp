#include "Path.h"

Path::Path(const std::vector<Tile*> newPath) : currentStep(newPath.size()), path(newPath) {

}

Path::~Path() {
	path.clear();
}

Tile* Path::next() {
	currentStep--;

	return current();
}

Tile* Path::current() {
	if (currentStep < 0 || currentStep >= path.size())
		return nullptr;

	return path[currentStep];
}