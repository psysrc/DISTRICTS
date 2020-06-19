#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <vector>

class Tile;

class Path {
private:
	int currentStep;
	std::vector<Tile*> path;
public:
	Path(const std::vector<Tile*>);
	~Path();
	Tile* next();
	Tile* current();
};

#endif /* SRC_PATH_H_ */
