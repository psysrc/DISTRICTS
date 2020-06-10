# DISTRICTS makefile
# Author: Samuel Copping <sam.copping@yahoo.com>


### BUILD FLAGS ###
BUILD_FLAGS := -pthread -Wall -Wextra -Wpedantic
INCLUDE_PATHS := -I src/


### LIBRARIES ###
LIBS := -lncurses


### SOURCE FILES ###
SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*/*.cpp)


### OBJECT FILES ###
OBJ_DIR := bin
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_SUB_DIRS := $(sort $(dir $(OBJ_FILES)))
EXE_NAME := DISTRICTS
EXE := $(OBJ_DIR)/$(EXE_NAME)


### RULES ###
all: $(EXE)

# Main executable
$(EXE): $(OBJ_FILES) | $(OBJ_DIR)
	@g++ $(BUILD_FLAGS) $(INCLUDE_PATHS) $^ -o $@ $(LIBS)
	@echo "Build complete."

# All object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@g++ -c $(BUILD_FLAGS) $(INCLUDE_PATHS) $< -o $@ $(LIBS)

# Object file directory and subdirectories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_SUB_DIRS)

# Clean
clean:
	@rm -rf $(OBJ_DIR)

# Phony
.PHONY: all clean
