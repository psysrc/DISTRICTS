#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include "Entity.h"

class Tree : public Entity {
public:
	Tree(District*);
	virtual ~Tree();
	virtual void simulate() override;
};

#endif /* SRC_TREE_H_ */
