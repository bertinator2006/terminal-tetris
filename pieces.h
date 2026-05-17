#ifndef PIECES_H
#define PIECES_H

#include <stdint.h>

#define NUM_PIECES 7

typedef enum
{
    TETROMINO_I, 
    TETROMINO_J, 
    TETROMINO_L, 
    TETROMINO_O, 
    TETROMINO_S, 
    TETROMINO_Z,
    TETROMINO_T,
    TETROMINO_NONE,
} PieceType;

extern const uint16_t tetrominoes[NUM_PIECES][4];

#endif
