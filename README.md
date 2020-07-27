# Welcome to the DISTRICTS GitHub page
DISTRICTS is a work-in-progress procedural base building and management game. It is heavily inspired by Dwarf Fortress in its style and functionality.
Currently the game is very limited, and right now couldn't really be classed as a proper game, but this will hopefully change in the near future as gameplay features are added and the project expands over time.

## Building the game
Right now the game is only being developed and tested on Linux. If you have a burning desire to play the game on Windows or MacOS, let me know so I can start looking into it.
To build the game for Linux, simply run the makefile in the top-level directory by running the command `make` or `make all`. All binaries for the game will be stored in a `bin` directory, including the DISTRICTS executable. The game must build against `ncurses`, so this must be available on your system - it should be available within the `libncurses5-dev` package through your package manager.

## Gameplay features
The game is currently very limited in terms of gameplay features, but nonetheless, here is what is currently available:
- Dynamic district generation (plains, water, stone, trees & saplings)
- A single citizen which will perform tasks that the player issues
- The player can tell the citizen to cut down trees and build bridges over water

## Controls
- `SPACE` to pause and unpause the game
- A list of player commands is shown while the game is paused
  - `A` to cut down a tree
  - `B` to build a bridge
- After selecting a command, use the `ARROW KEYS` to move the highlighted tile
- Hit `ENTER` to confirm the command on the highlighted tile
- Hit `Q` to cancel a selected command
- Hit `Q` twice to quit the game if no other command is selected

## Bugs, improvements & suggestions
Please let me know your thoughts on the game as it progresses! Whether you've found a bug, really like a certain feature, really hate a certain feature, or just have some ideas about what could be included in the game - I'd love to hear what you have to say!
