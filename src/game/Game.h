#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <thread>

class District;

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::unique_ptr<District> upDistrict;

	void unpause();
	void waitForPause();
public:
	Game();
	~Game();
	bool handleCommands();
	void play();
	void pause();
	void gameOver() const;
};

#endif /* GAME_H_ */
