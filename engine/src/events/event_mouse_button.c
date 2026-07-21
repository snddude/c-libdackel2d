#include "events/event_mouse_button.h"

#include <SDL3/SDL.h>

EventMouseButton event_mouse_button_create(SDL_Event event)
{
    return (EventMouseButton){
        .pressed = event.button.clicks >= 0,
        .double_click  = event.button.clicks >= 2,
        .button = event.button.button
    };
}