#pragma once

#include <SDL3/SDL.h>

typedef struct event_mouse_wheel
{
    float horizontal;
    float vertical;

} EventMouseWheel;

EventMouseWheel event_mouse_wheel_create(SDL_Event event);
