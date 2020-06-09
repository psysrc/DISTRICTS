# DISTRICTS makefile
# Author: Samuel Copping <sam.copping@yahoo.com>


### BUILD FLAGS ###
FLAGS := -pthread


### INCLUDE PATHS ###
INCLUDES := -I src/


### SOURCE FILES ###
SOURCES = \
	$(SOURCE_COMMANDS) \
	$(SOURCE_ENTITIES) \
	$(SOURCE_GAME) \
	$(SOURCE_PATHFINDING) \
	$(SOURCE_TASKS) \
	$(SOURCE_UI)

SOURCE_COMMANDS := $(wildcard src/commands/*.cpp)
SOURCE_ENTITIES := $(wildcard src/entities/*.cpp)
SOURCE_GAME := $(wildcard src/game/*.cpp)
SOURCE_PATHFINDING := $(wildcard src/pathfinding/*.cpp)
SOURCE_TASKS := $(wildcard src/tasks/*.cpp)
SOURCE_UI := $(wildcard src/ui/*.cpp)


### LIBRARIES ###
LIBS := -lncurses


### RULES ###
all: DISTRICTS

DISTRICTS: bin $(SOURCES)
	@echo "Building DISTRICTS..."
	@g++ $(FLAGS) $(INCLUDES) $(SOURCES) -o bin/$@ $(LIBS)
	@echo "Done."

bin:
	@mkdir bin
	@echo "Created bin directory."

clean:
	@rm -rf bin/
	@echo "Finished cleaning."

.PHONY: all clean
