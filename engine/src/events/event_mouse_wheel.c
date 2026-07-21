#include "events/event_mouse_wheel.h"

#include <SDL3/SDL.h>

EventMouseWheel event_mouse_wheel_create(SDL_Event event)
{
    return (EventMouseWheel){
        .horizontal = event.wheel.x,
        .vertical = event.wheel.y
    };
}
