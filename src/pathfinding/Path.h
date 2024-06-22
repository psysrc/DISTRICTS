#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <vector>

class DeprecatedTile;

class Path
{
public:
	Path(const std::vector<DeprecatedTile *>);
	~Path();
	DeprecatedTile *next();
	DeprecatedTile *current() const;
	DeprecatedTile *end() const;

private:
	std::size_t currentStep;
	std::vector<DeprecatedTile *> path;
	bool finished = false;
};

#endif /* SRC_PATH_H_ */
