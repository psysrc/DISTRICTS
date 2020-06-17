#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>

class District;
// class GameSystem;

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::shared_ptr<District> spDistrict;
	// std::vector<GameSystem> gameSystems;

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
