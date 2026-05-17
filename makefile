all:
	gcc main.c generation.c pieces.c -o tetris

run:
	./tetris