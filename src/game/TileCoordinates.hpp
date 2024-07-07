#ifndef TILECOORDINATES_H_
#define TILECOORDINATES_H_

#include <functional>

struct TileCoordinates
{
	TileCoordinates();
	TileCoordinates(short x, short y);

	~TileCoordinates();

	bool operator==(const TileCoordinates &) const;
	bool operator!=(const TileCoordinates &) const;
	bool operator<(const TileCoordinates &) const;

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
