#include "pieces.h"

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
    
} RotationIndex;

void load_offsets_x(int offsets_x[6], int offsets_y[6], int curr_rotation, int new_rotation, PieceType pt)
{
    offsets_x[0] = 0;
    offsets_y[0] = 0;
    // for rotation index to SRS system rotation conversion
    // 0 == 0 || R == 1 || 2 == 2 || L == 3
    if (pt == TETROMINO_I)
    {
        int x_offsets
    }
}
