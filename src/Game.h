#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <stdio.h>
#include "Map.h"

using namespace std;

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
