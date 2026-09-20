#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>

#define TETRIS_GRID_HEIGHT 20
#define TETRIS_GRID_WIDTH 10

typedef struct game *TETRIS_Game;

typedef struct {
    uint8_t cells[TETRIS_GRID_HEIGHT * TETRIS_GIRD_WIDTH];
} TETRIS_Grid;
// Initialiser
Game TETRIS_create_game(void);
void TETRIS_destroy_game(TETRIS_Game g);

// Accessing board information
TETRIS_Grid TETRIS_get_grid(TETRIS_Game g);
uint16_t TETRIS_get_held_piece(TETRIS_Game g);
int TETRIS_get_score(TETRIS_Game g);
uint8_t TETRIS_get_last_status(TETRIS_Game g);

// Piece falling logic
void TETRIS_next_frame(TETRIS_Game g);
void TETRIS_soft_drop(TETRIS_Game g);
void TETRIS_hard_drop(TETRIS_Game g);
void TETRIS_clear_rows(TETRIS_Game g);
void TETRIS_move_right(TETRIS_Game g);
void TETRIS_move_left(TETRIS_Game g);
void TETRIS_rotate(TETRIS_Game g);
void TETRIS_hold_piece(TETRIS_Game g);

#endif
