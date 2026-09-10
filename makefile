SRC=src/
SRCFILES=$(SRC)/main.c $(SRC)/generation.c $(SRC)/vector.c $(SRC)/pieces.c $(SRC)/display.c

all:
	gcc $(SRCFILES) -o tetris

run:
	./tetris
