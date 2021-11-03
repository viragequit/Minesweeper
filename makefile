#OBJS specifies which files to compile as part of the project
OBJS = 	main.cpp Tile.cpp Grid.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = 

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = 

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = minesweeper.exe

#This is the target that compiles our executable
all:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm *.o $(OBJ_NAME)
