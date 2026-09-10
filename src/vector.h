#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector2d {
    int x;
    int y;
} Vector2d;

Vector2d vector_add(Vector2d a, Vector2d b);

#endif
