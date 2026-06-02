all:
	gcc main.c generation.c pieces.c display.c -o tetris

run:
	./tetris