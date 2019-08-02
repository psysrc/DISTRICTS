#ifndef GAME_H_
#define GAME_H_

#include "Constants.h"
#include <iostream>
#include "District.h"
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <pthread.h>



class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	District* pDistrict;
	WINDOW* mapWindow;
	WINDOW* activityWindow;
	WINDOW* debugWindow;

	void unpause();
public:
	Game();
	~Game();
	void play();
	void pause();
	void displayActivityMessage(const char* str);
	void displayDebugMessage(std::string str);
	void displayDebugMessage(const char* str);
	void UpdateUI();
	void gameOver();
};

#endif /* GAME_H_ */
