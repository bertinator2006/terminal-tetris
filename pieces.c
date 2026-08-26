#include "pieces.h"

static void load_offsets_x_I(int offsets_x[5], int offsets_y[5], int curr_rotation, int new_rotation);


const uint16_t tetrominoes[NUM_PIECES][4] = {
    // Shape I
    {0x0f00, 0x4444, 0x00F0, 0x2222},

    // Shape J
    {0x1700, 0x6220, 0x0740, 0x2230},

    // Shape L
    {0x4700, 0x2260, 0x0710, 0x3220},

    // Shape O
    {0x6600, 0x6600, 0x6600, 0x6600},

    // Shape S
    {0x6300, 0x2640, 0x0630, 0x1320},

    // Shape Z
    {0x3600, 0x2640, 0x0630, 0x1320},

    // Shape T
    {0x2700, 0x2620, 0x0720, 0x2320}
};

typedef enum
{
    ROTATION_0,
    ROTATION_1,
    ROTATION_2,
    ROTATION_3
} RotationIndex;


void load_offsets_x(int offsets_x[5], int offsets_y[5], int curr_rotation, int new_rotation, PieceType pt)
{
    // https://tetris.wiki/Tetris_Guideline
    offsets_x[0] = 0;
    offsets_y[0] = 0;
    
    // I piece has different offsets than the other pieces
    if (pt == TETROMINO_I)
    {
        load_offsets_x_I(offsets_x, offsets_y, curr_rotation, new_rotation);
        return;
    }

    // all other pieces have the same offsets

    
}

static void load_offsets_x_I(int offsets_x[5], int offsets_y[5], int curr_rotation, int new_rotation)
{
    if (curr_rotation == ROTATION_0 && new_rotation == ROTATION_1)
    {
        offsets_x[1] = -2;
        offsets_y[1] = 0;
        offsets_x[2] = 1;
        offsets_y[2] = 0;
        offsets_x[3] = -2;
        offsets_y[3] = -1;
        offsets_x[4] = 1;
        offsets_y[4] = 2;
    }
    else if (curr_rotation == ROTATION_1 && new_rotation == ROTATION_0)
    {
        offsets_x[1] = 2;
        offsets_y[1] = 0;
        offsets_x[2] = -1;
        offsets_y[2] = 0;
        offsets_x[3] = 2;
        offsets_y[3] = 1;
        offsets_x[4] = -1;
        offsets_y[4] = -2;
    }
}
