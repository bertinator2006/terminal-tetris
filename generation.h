#ifndef GENERATION_H
#define GENERATION_H

#define NUM_UNIQUE_PIECES 7

typedef enum
{
    TETROMINO_NONE,
    TETROMINO_I, 
    TETROMINO_J, 
    TETROMINO_L, 
    TETROMINO_O, 
    TETROMINO_S, 
    TETROMINO_Z,
    TETROMINO_T,
} PieceType;

typedef struct generator *Generator;

Generator create_generator(void);
PieceType gen_random_piecetype(Generator gen);
void destroy_generator(Generator gen);

#endif
