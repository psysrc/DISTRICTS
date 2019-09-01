#include "Path.h"

Path::Path(const std::vector<Tile*> newPath) : currentStep(newPath.size()), path(newPath) {
//	UI::displayDebugMessage("Path object created.");
}

Path::~Path() {
	path.clear();
//	UI::displayDebugMessage("Path object destroyed.");
}

Tile* Path::next() {
	currentStep--;

	if (currentStep < 0)
		return nullptr;

	return path[currentStep];
}

