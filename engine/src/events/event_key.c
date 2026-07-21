#include "events/event_key.h"

#include <SDL3/SDL.h>

EventKey event_key_create(SDL_Event event)
{
    return (EventKey){
        .echo = event.key.repeat,
        .pressed = event.key.down,
        .label = SDL_GetKeyName(event.key.key),
        .key = event.key.key,
    };
}
