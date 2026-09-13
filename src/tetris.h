#ifndef TETRIS_H
#define TETRIS_H

typedef struct game *Game;

// Initialiser
Game create_game(void);
void destroy_game(Game g);

// Piece falling logic
void next_frame(Game g);
void soft_drop(Game g);
void hard_drop(Game g);
void clear_rows(Game g);

// Movement logic
void move_left(Game g);
void move_right(Game g);
void load_piecetype(Game g, PieceType pt);
bool check_can_move(Game g, Direction d);

// Level related logic
int get_level(Game g);

// Rotation logic
void rotate_left(Game g);
void rotate_right(Game g);

#endif