#include "input/input.h"

#include <SDL3/SDL.h>

int input_get_axis(key_code_t negative, key_code_t positive)
{
    const bool *keys = SDL_GetKeyboardState(NULL);
    return keys[SDL_GetScancodeFromKey(positive, NULL)] - keys[SDL_GetScancodeFromKey(negative, NULL)];
}

Vector2 input_get_vector(key_code_t left, key_code_t right, key_code_t down, key_code_t up)
{
    const bool *keys = SDL_GetKeyboardState(NULL);
    Vector2 vec = VECTOR2_ZERO;

    vec.x = keys[SDL_GetScancodeFromKey(right, NULL)] - keys[SDL_GetScancodeFromKey(left, NULL)];
    vec.y = keys[SDL_GetScancodeFromKey(down, NULL)] - keys[SDL_GetScancodeFromKey(up, NULL)];

    return vec;
}
