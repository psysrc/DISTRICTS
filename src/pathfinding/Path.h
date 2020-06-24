#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <vector>

class Tile;

class Path {
private:
	std::size_t currentStep;
	std::vector<Tile*> path;
	bool finished = false;
public:
	Path(const std::vector<Tile*>);
	~Path();
	Tile* next();
	Tile* current() const;
	Tile* end() const;
};

#endif /* SRC_PATH_H_ */
