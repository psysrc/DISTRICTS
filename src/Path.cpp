#include "Path.h"

Path::Path(const std::vector<Tile*> newPath) : currentStep(0), path(newPath) {

}

Path::~Path() {

}

Tile* Path::next() {
	currentStep++;

	return path[currentStep];
}

