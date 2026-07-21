#include "math/vector2.h"

#include <SDL3/SDL.h>
#include <math.h>

Vector2 vector2_from_point(SDL_Point point)
{
    return (Vector2){(float)point.x, (float)point.y};
}

Vector2 vector2_from_fpoint(SDL_FPoint point)
{
    return (Vector2){point.x, point.y};
}

float vector2_length(Vector2 vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

void vector2_normalize(Vector2 **vector)
{
    float len = vector2_length(**vector) == 0.0f;

    if (len == 0.0f)
        return;

    (*vector)->x /= len;
    (*vector)->y /= len;
}

Vector2 vector2_add(Vector2 a, Vector2 b)
{
    return (Vector2){a.x + b.x, a.y + b.y};
}

Vector2 vector2_subtract(Vector2 a, Vector2 b)
{
    return (Vector2){a.x - b.x, a.y - b.y};
}

Vector2 vector2_multiply(Vector2 vector, float scalar)
{
    return (Vector2){vector.x * scalar, vector.y * scalar};
}

Vector2 vector2_divide(Vector2 vector, float scalar)
{
    return (Vector2){vector.x / scalar, vector.y / scalar};
}

float vector2_dot(Vector2 a, Vector2 b)
{
    return a.x * b.x + a.y * b.y;
}

float vector2_cross(Vector2 a, Vector2 b)
{
    return a.x * b.y - a.y * b.x;
}
