#include "input/input.h"

#include "input/key_code.h"
#include "math/vector2.h"

#include <SDL3/SDL.h>

int input_get_axis(KeyCode negative, KeyCode positive)
{
    const bool *keys = SDL_GetKeyboardState(NULL);
    return keys[SDL_GetScancodeFromKey(positive, NULL)] - keys[SDL_GetScancodeFromKey(negative, NULL)];
}

Vector2 input_get_vector(KeyCode left, KeyCode right, KeyCode down, KeyCode up)
{
    const bool *keys = SDL_GetKeyboardState(NULL);
    Vector2 vec = VECTOR2_ZERO;

    vec.x = keys[SDL_GetScancodeFromKey(right, NULL)] - keys[SDL_GetScancodeFromKey(left, NULL)];
    vec.y = keys[SDL_GetScancodeFromKey(down, NULL)] - keys[SDL_GetScancodeFromKey(up, NULL)];

    return vec;
}
