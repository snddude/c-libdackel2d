#pragma once

#include <SDL3/SDL.h>

typedef enum event_type
{
    EventType_Unhandled = 0,
    EventType_Key,
    EventType_MouseButton,
    EventType_MouseWheel,
    EventType_MouseMotion

} EventType;

typedef struct event
{
    bool handled;
    EventType type;

    void *sub_event;

} Event;

Event event_create(SDL_Event native_event);
