#pragma once

#include <SDL3/SDL.h>

typedef enum
{
    MouseButton_Left = SDL_BUTTON_LEFT,
    MouseButton_Middle = SDL_BUTTON_MIDDLE,
    MouseButton_Right = SDL_BUTTON_RIGHT,
    MouseButton_Side1 = SDL_BUTTON_X1,
    MouseButton_Side2 = SDL_BUTTON_X2,
} mouse_button_t;
