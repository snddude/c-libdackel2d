#pragma once

typedef enum event_type
{
    Event_Key = 0,
    Event_MouseButton,
    Event_MouseWheel,
    Event_MouseMotion

} EventType;

typedef struct event
{
    void *super_type;
    EventType type;

} Event;
