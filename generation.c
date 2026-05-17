#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "generation.h"
#include "pieces.h"

struct generator {
    PieceType queue[NUM_PIECES];
    int next_queue_index;
};

static bool seeded = false;

static void shuffle_queue(Generator gen);

// returns a new generator
// only works once per program
Generator create_generator(void)
{
    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }
    Generator gen = malloc(sizeof(struct generator));
    for (int i = 0; i < NUM_PIECES; i++)
    {
        gen->queue[i] = i;
    }
    gen->next_queue_index = 0;
    shuffle_queue(gen);
    return gen;
};

PieceType gen_random_piecetype(Generator gen)
{
    int i = gen->next_queue_index;
    if (i == NUM_PIECES)
    {
        shuffle_queue(gen);
        i = 0;
    }
    
    PieceType pt = gen->queue[i];

    gen->next_queue_index = i + 1;
    return pt;
};

void destroy_generator(Generator gen)
{
    free(gen);
};

static void shuffle_queue(Generator gen)
{
    for (int i = NUM_PIECES - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        PieceType temp = gen->queue[i];
        gen->queue[i] = gen->queue[j];
        gen->queue[j] = temp;
    }
}