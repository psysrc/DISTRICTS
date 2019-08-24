#ifndef GAME_H_
#define GAME_H_

#include "Constants.h"
#include <iostream>
#include <memory>
#include "District.h"
#include <chrono>
#include <thread>		// sleep_for, pthread_*
#include "PlayerCommand.h"
#include "UserInterface.h"

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::shared_ptr<District> pDistrict;
	std::unique_ptr<pthread_t> pPauseThread;

	void unpause();
public:
	Game();
	~Game();
	int handleCommands();
	void play();
	void pause();
	void gameOver() const;
};

#endif /* GAME_H_ */
