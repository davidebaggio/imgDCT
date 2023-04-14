BUILD:= ./build
LIB:= $(BUILD)/lib
EXE:= $(BUILD)/executable
INCLUDE:= ./include
SRC:= ./src
SDL2I:= ./SDL2/include
SDL2L:= ./SDL2/lib
LIBIMG:= $(LIB)/libimg.a

CC:= g++
CFLAGS:= -std=c++17 -I$(INCLUDE) -I$(SDL2I) -Wall -Wextra
LFLAGS:= -lSDL2 -lSDL2main -lSDL2_image

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    detected_OS := Windows
else
    detected_OS := $(shell uname)  # same as "uname -s"
endif

ifeq ($(detected_OS),Windows)
    LFLAGS += -L$(SDL2L)
endif

all: lib test

lib:
	$(CC) $(CFLAGS) -c $(SRC)/imagehandler.cpp $(LFLAGS) -o $(BUILD)/imagehandler.o
	ar ruv $(LIB)/libimg.a ./build/imagehandler.o
	ranlib $(LIB)/libimg.a

test:
	$(CC) $(CFLAGS) ./tests/main.cpp $(LIBIMG) $(LFLAGS) -o $(EXE)/main

clear:
	rm ./build/*.o
	rm $(LIBIMG)
	rm $(EXE)/*.exe
#g++ -std=c17++ main.cpp -I{Path to SDL2\include} -L{Path to SDL2\lib} -Wall -lmingw32 -lSDL2main  -o main
