#ifndef SRC_SAPLING_H_
#define SRC_SAPLING_H_

#include "Entity.h"
#include "Tile.h"
#include "District.h"

class Sapling : public Entity {
public:
	Sapling(District*);
	virtual ~Sapling();
	virtual void simulate() override;
};

#endif /* SRC_SAPLING_H_ */
