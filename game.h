#ifndef GAME_H
#define GAME_H

#include "pieces.h"

#define GRID_HEIGHT 23
#define VISIBLE_GRID_HEIGHT 20
#define GRID_WIDTH 10
#define MAX_PIECE_WIDTH 4
#define MAX_PIECE_HEIGHT 4

typedef enum {
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
    DIRECTION_DOWN,
    DIRECTION_UP,
} Direction;

typedef struct vector2d {
    int x;
    int y;
} Vector2d;

typedef enum
{
    COLOR_LIGHTBLUE,
    COLOR_DARKBLUE,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_NONE,
} Color;

struct game {
    Color grid[GRID_HEIGHT][GRID_WIDTH];
    PieceType curr_piece_type;
    Vector2d curr_piece_pos;
    Color curr_piece_color;
    Color curr_piece_grid[MAX_PIECE_HEIGHT][MAX_PIECE_WIDTH];
    int currRotation;
};

typedef struct game *Game;

// Initialiser
Game create_game(void);
void destroy_game(Game g);

// Display and Inputg
void display_grid(Game g);

// Piece falling logic
int piece_fall(Game g);
void soft_drop_piece(Game g);
void hard_drop_piece(Game g);

// Movement logic
void move_left(Game g);
void move_right(Game g);
void load_piecetype(Game g, PieceType pt);
bool check_can_move(Game g, Direction d);

// Rotation logic
void rotate_left(Game g);
void rotate_right(Game g);
bool check_can_rotate(Game g);

#endif
