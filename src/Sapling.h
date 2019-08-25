#ifndef SRC_SAPLING_H_
#define SRC_SAPLING_H_

#include "Entity.h"

class Sapling : public Entity {
public:
	Sapling();
	virtual ~Sapling();
	virtual void simulate() override;
};

#endif /* SRC_SAPLING_H_ */
