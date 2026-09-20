#pragma once

#include "input/key_code.h"
#include "input/mouse_button.h"

#include <SDL3/SDL.h>
#include <vec2.h>
#include <stdbool.h>

typedef struct
{
    bool handled;
    enum
    {
        EVENT_TYPE_UNHANDLED = 0,
        EVENT_TYPE_KEY,
        EVENT_TYPE_MOUSEBUTTON,
        EVENT_TYPE_MOUSEWHEEL,
        EVENT_TYPE_MOUSEMOTION
    } type;
    union
    {
        struct { bool echo; bool pressed; const char *label; key_code_t code; } key;
        struct { bool pressed; bool double_click; mouse_button_t button; } mouse_button;
        struct { float horizontal; float vertical; } mouse_wheel;
        struct { vec2i_t absolute; vec2i_t relative; } mouse_motion;
    };
} event_t;

void event_init(event_t *self, SDL_Event native_event);
