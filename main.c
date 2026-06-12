#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "display.h"
#include "generation.h"
// https://tetris.wiki/Tetris_Guideline
// https://tetris.wiki/images/6/67/TGM_Legend_Tetra_SRS.png

// Scoring Logic
static void add_score(Game g, int num_rows_cleared);

Generator gen;

int main(void)
{
    Game game = create_game();
    gen = create_generator();
    PieceType piece_t = gen_random_piecetype(gen);
    load_piecetype(game, piece_t);

    bool quit = false;
    
    while (!quit)
    {
        display_grid(game);
        Command cmd = get_command();
        int ret;
        switch (cmd)
        {
            case CMD_QUIT:      quit = true;        break;
            case CMD_LEFT:      move_left(game);    break;
            case CMD_RIGHT:     move_right(game);   break;
            case CMD_ROTATE_L:  rotate_left(game);  break;
            case CMD_ROTATE_R:  rotate_right(game); break;
            case CMD_HARD_DROP: hard_drop(game);    break;
            case CMD_NONE:      piece_fall(game);   break;
            default:            break;
        }
    }
    
    return 0;
}

// returns Game
// initialises grid to 0 and curr_piece_type to NULL
Game create_game(void)
{
    Game g = malloc(sizeof(struct game));
    if (g == NULL)
    {
        fprintf(stderr, "failed to allocate memory in create_game()\n");
        exit(1);
    }

    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for  (int y = 0; y < GRID_HEIGHT; y++)
        {
            g->grid[y][x] = COLOR_NONE;
        }
    }
    g->curr_piece_type = TETROMINO_NONE;

    g->rows_cleared = 0;
    g->score = 0;

    return g;
}

// moves piece down by one is possible
// otherwise sets the piece onto the grid
// return 0 if piece moved down by one
// return 1 if piece was set onto the grid
int piece_fall(Game g)
{
    if (check_can_move(g, DIRECTION_DOWN))
    {
        g->curr_piece_pos.y++;
        return 0;
    }

    for (int i = 0; i < MAX_PIECE_HEIGHT; i++)
    {
        for (int j = 0; j < MAX_PIECE_WIDTH; j++)
        {
            if (g->curr_piece_grid[i][j] == COLOR_NONE)
            {
                continue;
            }

            int final_x = g->curr_piece_pos.x + j;
            int final_y = g->curr_piece_pos.y + i;

            g->grid[final_y][final_x] = g->curr_piece_color;
        }
    }
    PieceType piece_t = gen_random_piecetype(gen);
    load_piecetype(g, piece_t);

    return 1;
}

void move_left(Game g)
{
    if (check_can_move(g, DIRECTION_LEFT)) {
        g->curr_piece_pos.x--;
    }

    return;
}

void move_right(Game g)
{
    if (check_can_move(g, DIRECTION_RIGHT)) {
        g->curr_piece_pos.x++;
    }

    return;
}

bool check_can_move(Game g, Direction d) {
    // represented as {dy, dx}
    int iter[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int dx = iter[d][1];
    int dy = iter[d][0];

    int new_piece_y = dy + g->curr_piece_pos.y;
    int new_piece_x = dx + g->curr_piece_pos.x;

    // Look through all the pieces
    for (int i = 0; i < MAX_PIECE_HEIGHT; i++) {
        for (int j = 0 ; j < MAX_PIECE_WIDTH; j++) {
            // Check if this tile has anything or not
            if (g->curr_piece_grid[i][j] == COLOR_NONE) {
                continue;
            }

            // Now, check if we were to move the tile if it will be in range
            int final_x = new_piece_x + j;
            int final_y = new_piece_y + i;
            if (final_x < 0 || final_x > GRID_WIDTH - 1) {
                return false;
            } else if (final_y < 0 || final_y > GRID_HEIGHT - 1) {
                return false;
            }

            // Check if the piece will collide into another piece
            if (g->grid[final_y][final_x] != COLOR_NONE) {
                return false;
            }

        }
    }

    return true;
}

// Loads piece into to current
void load_piecetype(Game g, PieceType pt)
{
    Color c = (Color)pt;

    g->curr_piece_type = pt;
    g->curr_piece_color = c;

    uint16_t bmp = tetrominoes[pt][0];

    uint16_t mask = 0x8000;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (bmp & mask)
            {
                g->curr_piece_grid[y][x] = c;
            }
            else
            {
                g->curr_piece_grid[y][x] = COLOR_NONE;
            }

            mask >>= 1;
        }
    }

    g->curr_piece_pos.y = 0;
    g->curr_piece_pos.x = 3;
    g->currRotation = 0;
}

void destroy_game(Game g)
{
    free(g);
}

// does not modify anything
// returns true if the rotation can happen
// returns false if rotation cannot happen
static bool can_rotate(Game g, Rotation rotation)
{
    
}

// TODO: implement this
void rotate_left(Game g)
{
    return;
}

// TODO: implement this
void rotate_right(Game g)
{
    return;
}

// Drops the thing as far down until it hits something
void hard_drop(Game g)
{
    // Piece_fall returns 1 if it cannot drop anymore
    while (piece_fall(g) != 1) {}
    return;
}

// Clears fully finished rows, and drops things above the rows
void clear_rows(Game g)
{
    bool mark_rows[20] = {true};

    int currRow = GRID_HEIGHT;
    int maxRow = GRID_HEIGHT - VISIBLE_GRID_HEIGHT;

    int startRowToDel = -1;
    int finRowToDel = -1;

    // Mark which rows need to be deleted
    for (int checkRow = currRow; checkRow >= maxRow; checkRow--) {
        mark_rows[currRow] = true;
        for (int i = 0 ; i < GRID_WIDTH; i++) {
            if (g->grid[checkRow][i] == COLOR_NONE) {
                mark_rows[currRow] = false;
            }
        }
    }

    // All good no rows to delete
    if (startRowToDel == -1) {
        return;
    }

    // Count how many rows we need to delete
    int nRowsToDel = startRowToDel - finRowToDel;

    // Wipe out the rows that we need to delete
    for (int i = startRowToDel; i >= finRowToDel; i--) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            g->grid[i][j] = COLOR_NONE;
        }
    }

    // Push any blocks above down by an amount
    for (int currRow = startRowToDel; currRow > 0; currRow--) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            g->grid[currRow + nRowsToDel][j] = g->grid[currRow][j];
        }
    }

    add_score(g, nRowsToDel);

    return;
}

static void add_score(Game g, int num_rows_cleared) 
{
    return;
}