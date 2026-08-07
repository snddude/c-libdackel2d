#include "core/event.h"

event_t event_create(SDL_Event native_event)
{
    event_t event;
    event.handled = false;

    switch (native_event.type)
    {
        case SDL_EVENT_KEY_DOWN: case SDL_EVENT_KEY_UP:   
            event.type = EventType_Key;
            event.key.echo = native_event.key.repeat;
            event.key.pressed = native_event.key.down;
            event.key.label = SDL_GetKeyName(native_event.key.key);
            event.key.code = native_event.key.key;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN: case SDL_EVENT_MOUSE_BUTTON_UP:
            event.type = EventType_MouseButton;
            event.mouse_button.pressed = native_event.button.down;
            event.mouse_button.double_click  = native_event.button.clicks >= 2;
            event.mouse_button.button = native_event.button.button;
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            event.type = EventType_MouseWheel;
            event.mouse_wheel.horizontal = native_event.wheel.x;
            event.mouse_wheel.vertical = native_event.wheel.y;
            break;
        case SDL_EVENT_MOUSE_MOTION:
            event.type = EventType_MouseMotion;
            event.mouse_motion.absolute = (Vector2){ .x = native_event.motion.x, .y = native_event.motion.y };
            event.mouse_motion.relative = (Vector2){ .x = native_event.motion.xrel, .y = native_event.motion.yrel };
            break;
        default:
            event.type = EventType_Unhandled;
            break;
    }

    return event;
}
