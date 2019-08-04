#ifndef SRC_PLAYERCOMMAND_H_
#define SRC_PLAYERCOMMAND_H_

/*
 * This class defines constants for handling user commands.
 * Note that letters are always lowercase. When the user inputs a capital letter it is converted to a lowercase letter first.
 */
class PlayerCommand {
public:
	PlayerCommand() = delete;	// Class cannot be instantiated (effectively static)

	static const int NullCmd = -1;	// Can be used as an initialiser/reset to convey the concept of "no command" or an error

	static const int Pause = ' ';
	static const int Unpause = ' ';
	static const int Quit = 'q';
	static const int BuildHouse = 'a';
};

#endif /* SRC_PLAYERCOMMAND_H_ */
