#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <vector>
#include <optional>
#include "game/TileCoordinates.h"

class Path
{
public:
	Path(const std::vector<TileCoordinates>);
	~Path();
	std::optional<TileCoordinates> next();
	std::optional<TileCoordinates> current() const;
	TileCoordinates end() const;

private:
	std::size_t currentStep;
	std::vector<TileCoordinates> path;
	bool finished = false;
};

#endif /* SRC_PATH_H_ */
