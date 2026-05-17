#include <stdbool.h>
#include "game.h"
#include "display.h"

static void print_block(Color c);

void display_grid(Game g) {
    // Loop through the rows
    int fallingBlockRow = g->curr_piece_pos.y;
    int fallingBlockCol = g->curr_piece_pos.x;

    int first_visible_row = GRID_HEIGHT - VISIBLE_GRID_HEIGHT;

    for (int cRow = first_visible_row; cRow < GRID_HEIGHT; cRow++)
    {
        // At the start of each row print a border to make it look good
        printf("||");
        for (int cCol = 0; cCol < GRID_WIDTH; cCol++) {
            // Check if the grid already has something
            bool isFallingBlockRowRange = (fallingBlockRow <= cRow && cRow <= fallingBlockRow + MAX_PIECE_HEIGHT);
            bool isFallingBlockColRange = (fallingBlockCol <= cCol && cCol <= fallingBlockCol + MAX_PIECE_WIDTH);
    
            if (g->grid[cRow][cCol] != COLOR_NONE) {
                // Print it, and just that
                Color colorToPrint = g->grid[cRow][cCol];
                print_block(colorToPrint);

            } else if (isFallingBlockRowRange && isFallingBlockColRange) {
                Color currPosCol = g->curr_piece_grid[cRow - fallingBlockRow][cCol - fallingBlockCol];
                // If there is something, print it
                if (currPosCol != COLOR_NONE) {
                    print_block(currPosCol);
                }

            } else {
                print_block(COLOR_NONE);
            }
        }

        // At the end print the border
        printf("||\n");
    }
}

static void print_block(Color c) {
    if (c == COLOR_LIGHTBLUE) {
        printf("\033[36m██\033[0m");

    } else if (c == COLOR_DARKBLUE) {
        printf("\033[34m██\033[0m");

    } else if (c == COLOR_ORANGE) {
        printf("\033[38;5;208m██\033[0m");

    } else if (c == COLOR_YELLOW) {
        printf("\033[33m██\033[0m");

    } else if (c == COLOR_GREEN) {
        printf("\033[32m██\033[0m");

    } else if (c == COLOR_RED) {
        printf("\033[31m██\033[0m");

    } else if (c == COLOR_MAGENTA) {
        printf("\033[35m██\033[0m");

        // No colour
    } else {
        printf("\033[30m██\033[0m");
    }

    return;
}