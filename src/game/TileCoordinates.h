#ifndef TILECOORDINATES_H_
#define TILECOORDINATES_H_

struct TileCoordinates {
	TileCoordinates(short x, short y) : x(x), y(y) {}

	~TileCoordinates() {}

	bool operator==(const TileCoordinates& b) const {
		return (x == b.x) && (y == b.y);
	}

	bool operator!=(const TileCoordinates& b) const {
		return !(*this == b);
	}

	short x;
	short y;
};

#endif /* TILECOORDINATES_H_ */