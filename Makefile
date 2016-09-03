OBJS = player.cpp sprite.cpp texture.cpp game.cpp sound.cpp 
OBJ = Simplrustic
CC = g++
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer	
COMPILER_FLAGS = -g -w -std=c++11

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ)


