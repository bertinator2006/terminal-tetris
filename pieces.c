#include "pieces.h"

static void load_offsets_I(int offsets_x[5], int offsets_y[5], RotationIndex curr_rotation, RotationIndex new_rotation);

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
    {0x3600, 0x4620, 0x0360, 0x2310},

    // Shape T
    {0x2700, 0x2620, 0x0720, 0x2320}
};

typedef struct
{
	int x;
	int y;
} Offset;

void load_offsets(int offsets_x[5], int offsets_y[5], RotationIndex curr_rotation, RotationIndex new_rotation, PieceType pt)
{
	// https://tetris.wiki/Tetris_Guideline

	if (pt == TETROMINO_I)
	{
		load_offsets_I(offsets_x, offsets_y, curr_rotation, new_rotation);
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		offsets_x[i] = offsets[curr_rotation][new_rotation][i].x;
		offsets_y[i] = offsets[curr_rotation][new_rotation][i].y;
	}
}

static const Offset offsets[4][4][5] = {
	[ROTATION_0][ROTATION_R] = {
		{ 0,  0},
		{-1,  0},
		{-1, -1},
		{ 0,  2},
		{-1,  2}
	},

	[ROTATION_R][ROTATION_0] = {
		{ 0,  0},
		{ 1,  0},
		{ 1,  1},
		{ 0, -2},
		{ 1, -2}
	},

	[ROTATION_R][ROTATION_2] = {
		{ 0,  0},
		{ 1,  0},
		{ 1,  1},
		{ 0, -2},
		{ 1, -2}
	},

	[ROTATION_2][ROTATION_R] = {
		{ 0,  0},
		{-1,  0},
		{-1, -1},
		{ 0,  2},
		{-1,  2}
	},

	[ROTATION_2][ROTATION_L] = {
		{ 0,  0},
		{ 1, -1},
		{ 1, -1},
		{ 0,  2},
		{ 1,  2}
	},

	[ROTATION_L][ROTATION_2] = {
		{ 0,  0},
		{-1,  1},
		{-1,  1},
		{ 0, -2},
		{-1, -2}
	},

	[ROTATION_L][ROTATION_0] = {
		{ 0,  0},
		{-1,  1},
		{-1,  1},
		{ 0, -2},
		{-1, -2}
	},

	[ROTATION_0][ROTATION_L] = {
		{ 0,  0},
		{ 1, -1},
		{ 1, -1},
		{ 0,  2},
		{ 1,  2}
	}
};

static const Offset offsets_I[4][4][5] = {
	[ROTATION_0][ROTATION_R] = {
		{ 0,  0},
		{-2,  0},
		{ 1,  0},
		{-2, -1},
		{ 1,  2}
	},

	[ROTATION_R][ROTATION_0] = {
		{ 0,  0},
		{ 2,  0},
		{-1,  0},
		{ 2,  1},
		{-1, -2}
	},

	[ROTATION_R][ROTATION_2] = {
		{ 0,  0},
		{-1,  0},
		{ 2,  0},
		{-1,  2},
		{ 2, -1}
	},

	[ROTATION_2][ROTATION_R] = {
		{ 0,  0},
		{ 1,  0},
		{-2,  0},
		{ 1, -2},
		{-2,  1}
	},

	[ROTATION_2][ROTATION_L] = {
		{ 0,  0},
		{ 2,  0},
		{-1,  0},
		{ 2,  1},
		{-1, -2}
	},

	[ROTATION_L][ROTATION_2] = {
		{ 0,  0},
		{-2,  0},
		{ 1,  0},
		{-2, -1},
		{ 1,  2}
	},

	[ROTATION_L][ROTATION_0] = {
		{ 0,  0},
		{ 1,  0},
		{-2,  0},
		{ 1, -2},
		{-2,  1}
	},

	[ROTATION_0][ROTATION_L] = {
		{ 0,  0},
		{-1,  0},
		{ 2,  0},
		{-1,  2},
		{ 2, -1}
	}
};

static void load_offsets_I(int offsets_x[5], int offsets_y[5], RotationIndex curr_rotation, RotationIndex new_rotation)
{
	for (int i = 0; i < 5; i++)
	{
		offsets_x[i] = offsets_I[curr_rotation][new_rotation][i].x;
		offsets_y[i] = offsets_I[curr_rotation][new_rotation][i].y;
	}
}
