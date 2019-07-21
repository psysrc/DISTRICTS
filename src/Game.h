#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "District.h"
#include <chrono>
#include <thread>

class Game {
private:
	bool gameOver;
	District* district;
public:
	Game();
	~Game();
	void play();
};

#endif /* GAME_H_ */
