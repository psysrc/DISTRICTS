#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>

class District;
class GameSystem;

class Game
{
public:
	Game();
	Game(unsigned int seed);
	~Game();

	void play();

private:
	bool gameIsOver;
	bool gameIsPaused;
	std::shared_ptr<District> spDistrict;
	std::vector<std::unique_ptr<GameSystem>> preUpdateGameSystems;
	std::vector<std::unique_ptr<GameSystem>> postUpdateGameSystems;

	bool handleCommands();
	void gameOver() const;
	void runPreUpdateGameSystems();
	void runPostUpdateGameSystems();
};

#endif /* GAME_H_ */
