#include "events/event.h"

#include "events/event_key.h"
#include "events/event_mouse_button.h"
#include "events/event_mouse_wheel.h"
#include "events/event_mouse_motion.h"

Event event_create(SDL_Event native_event)
{
    Event event;
    event.handled = false;
    switch (native_event.type)
    {
        case SDL_EVENT_KEY_DOWN: case SDL_EVENT_KEY_UP:
            EventKey key = event_key_create(native_event);
            event.super_type = (void *)&key;
            event.type = EventType_Key;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN: case SDL_EVENT_MOUSE_BUTTON_UP:
            EventMouseButton mb = event_mouse_button_create(native_event);
            event.super_type = (void *)&mb;
            event.type = EventType_MouseButton;
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            EventMouseWheel mw = event_mouse_wheel_create(native_event);
            event.super_type = (void *)&mw;
            event.type = EventType_MouseWheel;
            break;
        case SDL_EVENT_MOUSE_MOTION:
            EventMouseMotion mm = event_mouse_motion_create(native_event);
            event.super_type = (void *)&mm;
            event.type = EventType_MouseMotion;
            break;
        default:
            event.super_type = NULL;
            event.type = EventType_Unhandled;
            break;
    }

    return event;
}
