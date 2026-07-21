#include "events/event_mouse_motion.h"

#include <SDL3/SDL.h>
#include "math/vector2.h"

EventMouseMotion event_mouse_motion_create(SDL_Event event)
{
    return (EventMouseMotion){
        .absolute = (Vector2){.x = event.motion.x, .x = event.motion.y},
        .relative = (Vector2){.x = event.motion.xrel, .x = event.motion.yrel}
    };
}
