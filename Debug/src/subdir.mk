################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Citizen.cpp \
../src/District.cpp \
../src/Entity.cpp \
../src/Game.cpp \
../src/Main.cpp \
../src/Path.cpp \
../src/PathFinding.cpp \
../src/Sapling.cpp \
../src/Tile.cpp \
../src/Tree.cpp \
../src/UI.cpp 

OBJS += \
./src/Citizen.o \
./src/District.o \
./src/Entity.o \
./src/Game.o \
./src/Main.o \
./src/Path.o \
./src/PathFinding.o \
./src/Sapling.o \
./src/Tile.o \
./src/Tree.o \
./src/UI.o 

CPP_DEPS += \
./src/Citizen.d \
./src/District.d \
./src/Entity.d \
./src/Game.d \
./src/Main.d \
./src/Path.d \
./src/PathFinding.d \
./src/Sapling.d \
./src/Tile.d \
./src/Tree.d \
./src/UI.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


