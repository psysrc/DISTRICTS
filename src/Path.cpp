#include "Path.h"

Path::Path(const std::vector<Tile*> newPath) : currentStep(newPath.size()), path(newPath) {

}

Path::~Path() {
	path.clear();
}

Tile* Path::next() {
	currentStep--;

	if (currentStep < 0)
		return nullptr;

	return path[currentStep];
}

