#pragma once

#include <SDL3/SDL.h>

#define VECTOR2_ZERO (Vector2){0.0f, 0.0f}
#define VECTOR2_ONE (Vector2){1.0f, 1.0f}

#define VECTOR2_UP (Vector2){0.0f, -1.0f}
#define VECTOR2_LEFT (Vector2){-1.0f, 0.0f}
#define VECTOR2_DOWN (Vector2){0.0f, 1.0f}
#define VECTOR2_RIGHT (Vector2){1.0f, 0.0f}

typedef struct vector2
{
    float x;
    float y;

} Vector2;

Vector2 vector2_from_point(SDL_Point point);
Vector2 vector2_from_fpoint(SDL_FPoint point);

float vector2_length(Vector2 vector);
void vector2_normalize(Vector2 **vector);

Vector2 vector2_add(Vector2 a, Vector2 b);
Vector2 vector2_subtract(Vector2 a, Vector2 b);

Vector2 vector2_multiply(Vector2 vector, float scalar);
Vector2 vector2_divide(Vector2 vector, float scalar);

float vector2_dot(Vector2 a, Vector2 b);
float vector2_cross(Vector2 a, Vector2 b);
