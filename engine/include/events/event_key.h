#pragma once

#include <SDL3/SDL.h>
#include "input/key_code.h"

typedef struct event_key
{
    bool echo;
    bool pressed;
    const char *label;

    KeyCode key;

} EventKey;

EventKey event_key_create(SDL_Event event);
