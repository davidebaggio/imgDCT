BUILD:= ./build
INCLUDE:= ./include
SRC:= ./src
SDL2I:= ./SDL2/include
SDL2L:= ./SDL2/lib

CC:= g++
CFLAGS:= -std=c++2a -I$(INCLUDE) -I$(SDL2I) -Wall -Wextra
LFLAGS:= -L$(SDL2L) -lmingw32 -lSDL2 -lSDL2main -lSDL2_image

all:
	$(CC) $(CFLAGS) $(SRC)/main.cpp $(LFLAGS) -o $(BUILD)/main.exe

#g++ -std=c17++ main.cpp -I{Path to SDL2\include} -L{Path to SDL2\lib} -Wall -lmingw32 -lSDL2main  -o main