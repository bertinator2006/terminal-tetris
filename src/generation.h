#ifndef GENERATION_H
#define GENERATION_H

#include "pieces.h"

typedef struct generator *Generator;

Generator create_generator(void);
PieceType gen_random_piecetype(Generator gen);
void destroy_generator(Generator gen);

#endif
