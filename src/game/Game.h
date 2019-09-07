#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <thread>	// pthread_t

class District;

class Game {
private:
	bool gameIsOver;
	bool gameIsPaused;
	std::unique_ptr<District> upDistrict;
	std::unique_ptr<pthread_t> upPauseThread;

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
