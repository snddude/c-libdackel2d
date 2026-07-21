#pragma once

#include <SDL3/SDL.h>
#include "math/vector2.h"

typedef struct event_mouse_motion
{
    Vector2 absolute;
    Vector2 relative;

} EventMouseMotion;

EventMouseMotion event_mouse_motion_create(SDL_Event event);
