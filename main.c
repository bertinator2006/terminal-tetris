#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "pieces.h"
#include "display.h"
#include "generation.h"
#include "vector.h"
// https://tetris.wiki/Tetris_Guideline
// https://tetris.wiki/images/6/67/TGM_Legend_Tetra_SRS.png

// Scoring Logic
static void add_score(Game g, int num_rows_cleared);

// rotation logic
static void rotate(Game g, Rotation r);
static bool test_potential_position(Game g, Vector2d offset, uint16_t bitmap);
static void load_piecegrid(Game g, PieceType pt, Direction d);
static void delete_row(Game g, int row);
void clear_rows(Game g);

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
        // game->curr_piece_pos.y = 4;
        // game->curr_piece_pos.x = 3;
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

    clear_rows(g);

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
    Vector2d iter[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Vector2d new_piece_pos = vector_add(iter[d], g->curr_piece_pos);

    // Look through all the pieces
    for (int i = 0; i < MAX_PIECE_HEIGHT; i++) {
        for (int j = 0 ; j < MAX_PIECE_WIDTH; j++) {
            // Check if this tile has anything or not
            if (g->curr_piece_grid[i][j] == COLOR_NONE) {
                continue;
            }

            // Now, check if we were to move the tile if it will be in range
            Vector2d to_add;
            to_add.x = j;
            to_add.y = i;
            Vector2d final_pos = vector_add(new_piece_pos, to_add);
            if (final_pos.x < 0 || final_pos.x > GRID_WIDTH - 1) {
                return false;
            } else if (final_pos.y < 0 || final_pos.y > GRID_HEIGHT - 1) {
                return false;
            }

            // Check if the piece will collide into another piece
            if (g->grid[final_pos.y][final_pos.x] != COLOR_NONE) {
                return false;
            }
        }
    }

    return true;
}

// Loads piece into to current piece grid,
// sets the current piece type, color, direction, and position to default
void load_piecetype(Game g, PieceType pt)
{
    Color c = (Color)pt;

    g->curr_piece_type = pt;
    g->curr_piece_color = c;

    load_piecegrid(g, pt, 0);

    g->curr_piece_pos.y = 0;
    g->curr_piece_pos.x = 3;
    g->curr_piece_rotation_index = ROTATION_0;
}

void destroy_game(Game g)
{
    free(g);
}

// changes the curr piece grid to match the given piecetype
// not tied to any specific action
static void load_piecegrid(Game g, PieceType pt, Direction d)
{
    Color c = (Color)pt;

    uint16_t bitmap = tetrominoes[pt][d];

    uint16_t mask = 0x8000;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (bitmap & mask)
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
}

static void rotate(Game g, Rotation r)
{
    int new_rotation_index;
    if (r == ROTATION_LEFT)
    {
        new_rotation_index = (g->curr_piece_rotation_index + 1) % 4;
    }
    else if (r == ROTATION_RIGHT)
    {
        new_rotation_index = (g->curr_piece_rotation_index + 1) % 4;
    }

    Vector2d offsets[5];
    load_offsets(offsets, g->curr_piece_rotation_index, new_rotation_index, g->curr_piece_type);
    for (int i = 0; i < 5; i++)
    {
        if (test_potential_position(g, offsets[i], tetrominoes[g->curr_piece_type][new_rotation_index]))
        {
            g->curr_piece_pos.x += offsets[i].x;
            g->curr_piece_pos.y += offsets[i].y;
            g->curr_piece_rotation_index = new_rotation_index;
            load_piecegrid(g, g->curr_piece_type, new_rotation_index);
            return;
        }
    }
}

// Rotates the curr_piece anticlockwise
// Replaces the bitmap, and the curr piece grid
// uses Tetris SRS system for rotation
void rotate_left(Game g)
{
    rotate(g, ROTATION_LEFT);
}

// Rotates the curr_piece clockwise
// Replaces the bitmap, and the curr piece grid
// uses Tetris SRS system for rotation
void rotate_right(Game g)
{
    rotate(g, ROTATION_RIGHT);
}

// Tests a new position to see if we can rotate there.
static bool test_potential_position(Game g, Vector2d offset, uint16_t bitmap)
{
    Vector2d test_pos = vector_add(g->curr_piece_pos, offset);
    int currBitPos = 15;
    
    for (int i = test_pos.x; i < 4; i++) {
        for (int j = test_pos.y; j < 4; j++) {
            // If there is something in where we want to go, we cant rotate there
            int currBit = bitmap & (0b1 << currBitPos);
            currBitPos--;
            if (currBit == 1 && g->grid[i][j] != COLOR_NONE) {
                return false;
            }
        }
    }
    return true;
}

// Drops the thing as far down until it hits something
void hard_drop(Game g)
{
    // Piece_fall returns 1 if it cannot drop anymore
    while (piece_fall(g) != 1) {}
    return;
}

static void delete_row(Game g, int row)
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        g->grid[row][i] = COLOR_NONE;
    }

    for (int r = row - 1; r > 0; r--)
    {
        for (int x = 0; x < GRID_HEIGHT; x++)
        {
            g->grid[r + 1][x] = g->grid[r][x];
            g->grid[r][x] = COLOR_NONE;
        }
    }
}

static bool is_row_complete(Game g, int row)
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        if (g->grid[row][i] == COLOR_NONE)
        {
            return false;
        }
    }

    return true;
}

// Clears fully finished rows, and drops things above the rows
void clear_rows(Game g)
{
    // for each row
    //     if the row is complete
    //         delete the row
    //         move all previous rows downs
    int clear_count = 0;
    for (int row = 0; row < GRID_HEIGHT; row++)
    {
        if (is_row_complete(g, row))
        {
            clear_count++;
            delete_row(g, row);
        }
    }

    add_score(g, clear_count);

    return;
}

// Adds score based on the amount of rows cleared 
static void add_score(Game g, int num_rows_cleared) 
{
    return;
}

