#ifndef PIECES_H
#define PIECES_H

#include <stdint.h>
#include "game.h"

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

typedef enum
{
    ROTATION_0,
    ROTATION_R,
    ROTATION_2,
    ROTATION_L
} RotationIndex;

extern const uint16_t tetrominoes[NUM_PIECES][4];

void load_offsets(Vector2d offsets[5], RotationIndex curr_rotation, RotationIndex new_rotation, PieceType pt);


#endif
