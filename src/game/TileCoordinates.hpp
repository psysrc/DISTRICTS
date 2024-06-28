#ifndef TILECOORDINATES_H_
#define TILECOORDINATES_H_

#include <functional>

struct TileCoordinates
{
	TileCoordinates() : x(0), y(0) {}
	TileCoordinates(short x, short y) : x(x), y(y) {}

	~TileCoordinates() {}

	bool operator==(const TileCoordinates &b) const
	{
		return (x == b.x) && (y == b.y);
	}

	bool operator!=(const TileCoordinates &b) const
	{
		return !(*this == b);
	}

	short x;
	short y;
};

template <>
struct std::hash<TileCoordinates>
{
  std::size_t operator()(const TileCoordinates& k) const
  {
    // Compute individual hash values for first and second, and combine them using XOR and bit shifting:

    return ((std::hash<short>()(k.x) ^ (std::hash<short>()(k.y) << 1)) >> 1);
  }
};

#endif /* TILECOORDINATES_H_ */
