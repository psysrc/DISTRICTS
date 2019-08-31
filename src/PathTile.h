#ifndef SRC_PATHTILE_H_
#define SRC_PATHTILE_H_

class Tile;

class PathTile {
private:
	Tile* tile;
	int pathLength;
	int distRemaining;
public:
	PathTile(Tile*, int);
	~PathTile();
	Tile* getTile() const;
	int getDistRemaining() const;
	void setPathLength(int);
	int getPathLength() const;
};

#endif /* SRC_PATHTILE_H_ */
