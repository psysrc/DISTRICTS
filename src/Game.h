#ifndef GAME_H_
#define GAME_H_

#include "Constants.h"
#include <iostream>
#include "District.h"
#include <chrono>
#include <thread>
#include <ncurses.h>

class Game {
private:
	bool gameIsOver;
	District* pDistrict;
	WINDOW* mapWindow;
	WINDOW* activityWindow;
//	WINDOW* debugWindow;
public:
	Game();
	~Game();
	void play();
	void UpdateUI();
	void gameOver();
};

#endif /* GAME_H_ */
