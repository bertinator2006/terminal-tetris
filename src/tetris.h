#ifndef TETRIS_H
#define TETRIS_H

typedef struct game *TETRIS_Game;
typedef uint16_t TETRIS_Row;
typedef uint16_t TETRIS_PieceBitmap;

// Initialiser
Game TETRIS_create_game(void);
void TETRIS_destroy_game(Game g);

// Accessing board information
const TETRIS_Row *TETRIS_get_grid(Game g);
TETRIS_PieceBitmap TETRIS_get_held_piece(Game g);
int TETRIS_get_score(Game g);

// Piece falling logic
void TETRIS_next_frame(Game g);
void TETRIS_soft_drop(Game g);
void TETRIS_hard_drop(Game g);
void TETRIS_clear_rows(Game g);
void TETRIS_move_right(Game g);
void TETRIS_move_left(Game g);
void TETRIS_rotate(Game g);
void TETRIS_hold_piece(Game g);

#endif
