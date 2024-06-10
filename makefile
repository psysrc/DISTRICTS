# DISTRICTS makefile
# Author: Samuel Copping <sam.copping@yahoo.com>


### BUILD FLAGS ###
BUILD_FLAGS := -pthread -Wall -Wextra -Wpedantic -g3 -Werror
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


### CONFIG FILES ###
CFG_DIR := cfg


### CXX COMPILER ###
CXX ?= /usr/bin/g++


### RULES ###
all: $(EXE) $(OBJ_DIR)/$(CFG_DIR)

# Main executable
$(EXE): $(OBJ_FILES) | $(OBJ_DIR)
	$(CXX) $(BUILD_FLAGS) $(INCLUDE_PATHS) $^ -o $@ $(LIBS)
	@echo "Build complete."

# All object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -MMD -c $(BUILD_FLAGS) $(INCLUDE_PATHS) $< -o $@

# Object file directory and subdirectories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_SUB_DIRS)

# Pre-compiled object file dependencies, produced by $(CXX) -MMD
-include $(OBJ_DIR)/*/*.d

# Config files
$(OBJ_DIR)/$(CFG_DIR):
	rsync -rup $(CFG_DIR) $(OBJ_DIR)/

# Clean
clean:
	rm -rf $(OBJ_DIR)

# Phony
.PHONY: all clean

# Silence all recipes
.SILENT:
