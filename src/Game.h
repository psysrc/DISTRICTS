#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "District.h"
#include <chrono>
#include <thread>

class Game {
private:
	bool gameIsOver;
	District* district;
public:
	Game();
	~Game();
	void play();
	void gameOver();
};

#endif /* GAME_H_ */
