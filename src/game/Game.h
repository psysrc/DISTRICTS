#ifndef GAME_H_
#define GAME_H_

#include <memory>

class District;

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::shared_ptr<District> spDistrict;

	void pause();
	void unpause();
	bool handleCommands();
	void waitForPause();
	void gameOver() const;
public:
	Game();
	~Game();
	void play();
};

#endif /* GAME_H_ */
