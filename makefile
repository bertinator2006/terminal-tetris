SRC = $(wildcard src/*.c)
NEW_SRC = $(wildcard src_new/*.c)

tetris:
	gcc $(SRC) -o tetris

new:
	gcc $(NEW_SRC) -o tetris


run:
	./tetris
