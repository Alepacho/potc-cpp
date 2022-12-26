CC = g++ -O2
CFLAGS = -std=c++17 -Wall -g3
LFLAGS = `sdl2-config --libs` -lsdl2_image -lsdl2_mixer
IFLAGS = `sdl2-config --cflags` -I$(INC_PATH)

INC_PATH = ./inc/
SRC_PATH = ./src/
OUT_PATH = ./out/
BIN_PATH = ./bin/

all: clean main
	@echo "Done!"

mkdirs:
	mkdir -p out
	mkdir -p bin
	mkdir -p inc

clean:
	rm -rf $(BIN_PATH)game
	rm -rf $(OUT_PATH)*.o

main: mkdirs engine game
	$(CC) $(CFLAGS) $(SRC_PATH)main.cpp $(OUT_PATH)*.o $(IFLAGS) $(LFLAGS) -o $(BIN_PATH)game

engine: game.o engine.o sound.o screen.o art.o bitmap.o bitmap3d.o
	@echo "engine"

game: block.o level.o entity.o player.o enemy.o menu.o 
	@echo "game"

game.o:
	$(CC) $(CFLAGS) $(SRC_PATH)game.cpp $(IFLAGS) -c -o $(OUT_PATH)game.o

engine.o:
	$(CC) $(CFLAGS) $(SRC_PATH)engine.cpp $(IFLAGS) -c -o $(OUT_PATH)engine.o

screen.o:
	$(CC) $(CFLAGS) $(SRC_PATH)gui/screen.cpp $(IFLAGS) -c -o $(OUT_PATH)screen.o

block.o:
	$(CC) $(CFLAGS) $(SRC_PATH)level/block/block.cpp $(IFLAGS) -c -o $(OUT_PATH)block.o

level.o:
	$(CC) $(CFLAGS) $(SRC_PATH)level/level.cpp $(IFLAGS) -c -o $(OUT_PATH)level.o

entity.o:
	$(CC) $(CFLAGS) $(SRC_PATH)entities/entity.cpp $(IFLAGS) -c -o $(OUT_PATH)entity.o

player.o:
	$(CC) $(CFLAGS) $(SRC_PATH)entities/player.cpp $(IFLAGS) -c -o $(OUT_PATH)player.o

enemy.o:
	$(CC) $(CFLAGS) $(SRC_PATH)entities/enemy.cpp $(IFLAGS) -c -o $(OUT_PATH)enemy.o

bitmap.o:
	$(CC) $(CFLAGS) $(SRC_PATH)gui/bitmap.cpp $(IFLAGS) -c -o $(OUT_PATH)bitmap.o

bitmap3d.o:
	$(CC) $(CFLAGS) $(SRC_PATH)gui/bitmap3d.cpp $(IFLAGS) -c -o $(OUT_PATH)bitmap3d.o

menu.o:
	$(CC) $(CFLAGS) $(SRC_PATH)menu/menu.cpp $(IFLAGS) -c -o $(OUT_PATH)menu.o

art.o:
	$(CC) $(CFLAGS) $(SRC_PATH)art.cpp $(IFLAGS) -c -o $(OUT_PATH)art.o

sound.o:
	$(CC) $(CFLAGS) $(SRC_PATH)sound.cpp $(IFLAGS) -c -o $(OUT_PATH)sound.o
