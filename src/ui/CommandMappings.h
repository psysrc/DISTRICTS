#ifndef SRC_COMMANDMAPPINGS_H
#define SRC_COMMANDMAPPINGS_H

/*
 * This class defines constants for handling user key presses and translating them into game commands.
 * Note that letters are always lowercase. When the user inputs a capital letter it is converted to a lowercase letter first.
 */
class CommandMappings {
public:
	CommandMappings() = delete;	// Class cannot be instantiated (effectively static)

	static const int NullCmd = -1;	// Can be used as an initialiser/reset to convey the concept of "no command" or an error

	static const int PauseToggle = ' ';
	static const int Quit = 'q';
	static const int BuildHouse = 'a';
};

#endif /* SRC_COMMANDMAPPINGS_H */
