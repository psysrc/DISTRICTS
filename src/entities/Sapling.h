#ifndef SRC_SAPLING_H_
#define SRC_SAPLING_H_

#include "Entity.h"
#include "components/GrowComponent.h"

class District;

class Sapling : public Entity {
public:
	Sapling();
	virtual ~Sapling();
private:
	GrowComponent gp;
};

#endif /* SRC_SAPLING_H_ */
