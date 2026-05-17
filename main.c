#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "display.h"
#include "generation.h"
// https://www.google.com/search?q=tetris+wiki+for+implmentation&sca_esv=6ce64e4e4d3a8d9d&sxsrf=ANbL-n6OewMJEkXy7zbXKMoSmmnM5-UY1Q%3A1778760612837&ei=pLsFaqnUMqXI0-kPg_jD8AE&biw=1530&bih=768&ved=0ahUKEwiptt_T37iUAxUl5DQHHQP8EB4Q4dUDCBI&uact=5&oq=tetris+wiki+for+implmentation&gs_lp=Egxnd3Mtd2l6LXNlcnAiHXRldHJpcyB3aWtpIGZvciBpbXBsbWVudGF0aW9uMgcQIRgKGKABSKcdUIoEWNUccAF4AZABAJgB4gGgAYQZqgEGMC4xMy40uAEDyAEA-AEBmAISoAKxGcICChAAGEcY1gQYsAPCAg0QABiABBiKBRhDGLADwgIXEC4Y3AYYuAYY2gYY2AIYyAMYsAPYAQHCAhcQLhjYAhi4BhjaBhjcBhjIAxiwA9gBAcICBRAAGIAEwgIGEAAYFhgewgIIEAAYgAQYogTCAgUQABjvBcICCxAAGIAEGIoFGIYDwgIFECEYoAHCAgQQIRgVmAMAiAYBkAYUugYGCAEQARgZkgcGMS4xMi41oAeTM7IHBjAuMTIuNbgHqxnCBwYxMC43LjHIBxqACAE&sclient=gws-wiz-serp
// https://tetris.wiki/images/6/67/TGM_Legend_Tetra_SRS.png


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

int main(void)
{
    Game game = create_game();

    return 0;
}

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
    g->currRotation = 0;
    
    return g;
}

void display_grid(Game g) {


    return;
    
}


// moves piece down by one is possible
// otherwise sets the piece onto the grid
// return 0 if piece moved down by one
// return 1 if piece was set onto the grid
int piece_fall(Game g) {
    // If we can move down, move down
    if (check_can_move(g, DIRECTION_DOWN)) {
        // Move down
        g->curr_piece_pos.y++;
        return 0;
    // We cannot move down, set it     
    } else {
        // Loop through every piece
        for (int i = 0; i < MAX_PIECE_HEIGHT; i++) {
            for (int j = 0 ; j < MAX_PIECE_WIDTH; j++) {
                if (g->curr_piece_grid[i][j] == COLOR_NONE) {
                    continue;
                }

                // Set the piece at this position into the grid
                int final_x = g->curr_piece_pos.x + j;
                int final_y = g->curr_piece_pos.y = i;

                g->grid[final_x][final_y] = g->curr_piece_color;
            }
        }   

        return 1;
    }     
    return 0;
}

void soft_drop_piece(Game g);
void hard_drop_piece(Game g);

// TODO: implement this
void move_left(Game g)
{
    if (check_can_move(g, DIRECTION_RIGHT)) {
        g->curr_piece_pos.x--;
    }

    return;
}


// TODO: implement this
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
            } else if (final_y < 0) {
                return false;
            }

            // Check if the piece will collide into another piece
            if (g->grid[final_x][final_y] != COLOR_NONE) {
                return false;
            }

        }
    }

    return true;
}

// Loads piece into to current
void load_piecetype(Game g, PieceType pt)
{
    // Update data
    // This is an enum with the same fields and order
    Color c = pt;
    g->curr_piece_type = pt;
    g->curr_piece_color = c;

    uint16_t bmp = tetrominoes[pt][0];

    for (int y = 0; y < MAX_PIECE_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_PIECE_WIDTH; x++)
        {
            int i = y * MAX_PIECE_WIDTH + x;
            // 0b1 << 1 == 0b10
            if (bmp & (0x8000 >> i))
            {
                g->curr_piece_grid[y][x] = c;
            }
            else
            {
                g->curr_piece_grid[y][x] = COLOR_NONE;
            }
        }
    }

    g->curr_piece_pos.y = 0;    // All spawn at max height
    g->curr_piece_pos.x = 3;    // Add have this as the same

    g->currRotation = 0;

    return;
}


void destroy_game(Game g)
{
    free(g);
}
// TODO: implement this
void rotate_left(Game g);

// TODO: implement this
void rotate_right(Game g);

bool check_can_rotate(g);