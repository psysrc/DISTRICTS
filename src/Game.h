#ifndef GAME_H_
#define GAME_H_

#include "Constants.h"
#include <iostream>
#include <memory>
#include "District.h"
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <pthread.h>
#include "PlayerCommand.h"

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::shared_ptr<District> pDistrict;
	WINDOW* mapWindow;
	WINDOW* activityWindow;
	WINDOW* debugWindow;
	std::unique_ptr<pthread_t> pPauseThread;

	void unpause();
public:
	Game();
	~Game();
	int handleCommands();
	void play();
	void pause();
	void displayActivityMessage(const char* str);
	void displayDebugMessage(std::string str);
	void displayDebugMessage(const char* str);
	void updateUI();
	void gameOver();
};

#endif /* GAME_H_ */
