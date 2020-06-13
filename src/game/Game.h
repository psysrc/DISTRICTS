#ifndef GAME_H_
#define GAME_H_

#include <memory>

class District;

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::shared_ptr<District> spDistrict;

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
