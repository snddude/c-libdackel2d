#pragma once

#include "input/mouse_button.h"
#include <SDL3/SDL.h>

typedef struct event_mouse_button
{
    bool pressed;
    bool double_click;

    MouseButton button;

} EventMouseButton;

EventMouseButton event_mouse_button_create(SDL_Event event);
