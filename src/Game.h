#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "Map.h"

class Game {
private:
	bool gameOver;
	Map* map;
public:
	Game();
	~Game();
	void play();
};

#endif /* GAME_H_ */
