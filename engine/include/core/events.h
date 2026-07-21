#pragma once

#include "input/key_code.h"
#include "input/mouse_button.h"
#include "math/vector2.h"

enum EventType
{
    Key = 0,
    MouseButton,
    MouseWheel,
    MouseMotion
};

typedef struct event
{
    void *super_type;
    EventType type;

} Event;

typedef struct event_key
{
    bool pressed;
    const char *label;

    KeyCode key;

} EventKey;

typedef struct event_mouse_button
{
    bool pressed;
    bool double_click;

    MouseButton button;

} EventMouseButton;

typedef struct event_mouse_wheel
{
    float horizontal;
    float vertical;

} EventMouseWheel;

typedef struct event_mouse_motion
{
    Vector2 absolute;
    Vector2 relative;

} EventMouseMotion;
