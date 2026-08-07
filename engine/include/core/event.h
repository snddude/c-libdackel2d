#pragma once

#include "input/key_code.h"
#include "input/mouse_button.h"
#include "math/vector2.h"

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct
{
    bool handled;

    enum
    {
        EventType_Unhandled = 0,
        EventType_Key,
        EventType_MouseButton,
        EventType_MouseWheel,
        EventType_MouseMotion
    } type;

    union
    {
        struct { bool echo; bool pressed; const char *label; key_code_t code; } key;
        struct { bool pressed; bool double_click; mouse_button_t button; } mouse_button;
        struct { float horizontal; float vertical; } mouse_wheel;
        struct { Vector2 absolute; Vector2 relative; } mouse_motion;
    };

} event_t;

event_t event_create(SDL_Event native_event);
