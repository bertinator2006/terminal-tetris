all:
	gcc main.c generation.c pieces.c display.c vector.c -o tetris

run:
	./tetris