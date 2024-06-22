#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <vector>

class Tile;

class Path
{
public:
	Path(const std::vector<Tile *>);
	~Path();
	Tile *next();
	Tile *current() const;
	Tile *end() const;

private:
	std::size_t currentStep;
	std::vector<Tile *> path;
	bool finished = false;
};

#endif /* SRC_PATH_H_ */
