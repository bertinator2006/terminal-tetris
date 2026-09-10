#include "vector.h"

Vector2d vector_add(Vector2d a, Vector2d b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}