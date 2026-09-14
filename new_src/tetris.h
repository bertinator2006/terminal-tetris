#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>

#define TETRIS_GRID_WIDTH 10
#define TETRIS_GRID_HEIGHT 20
#define TETRIS_ROWS_CLEARED (1 << 0)
#define TETRIS_GAME_OVER (1 << 1)
#define TETRIS_TETRIS_PIECE_HELD (1 << 2)
#define TETRIS_PIECE_LOCKED (1 << 3)

typedef struct game *TETRIS_Game;
typedef struct {
	// each shape has a different value,
	// I is blue, J is orange, etc.
	uint8_t cells[GRID_HEIGHT][GRID_WIDTH];
} TETRIS_grid;

// Initiliase and close
Game TETRIS_create_game(void);
void TETRIS_destroy_game(Game g);

// Getters
void TETRIS_get_grid(Game g, TETRIS_grid *grid);
uint16_t TETRIS_get_held_piece(Game g);
int TETRIS_get_score(Game g);
void TETRIS_get_rows_cleared(Game g, int rows[4]);

// Input functions
void TETRIS_move_left(Game g);
void TETRIS_move_right(Game g);
void TETRIS_rotate(Game g);
void TETRIS_hold(Game g);
void TETRIS_hard_drop(Game g);
void TETRIS_soft_drop(Game g);

// Update state functions
void TETRIS_clear_rows(Game g);
void TETRIS_next_frame(Game g, float delta_time_s);

#endif
