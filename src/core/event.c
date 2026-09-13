#include "core/event.h"

void event_init(event_t *self, SDL_Event native_event)
{
    self->handled = false;

    switch (native_event.type)
    {
        case SDL_EVENT_KEY_DOWN: case SDL_EVENT_KEY_UP:   
            self->type = EventType_Key;
            self->key.echo = native_event.key.repeat;
            self->key.pressed = native_event.key.down;
            self->key.label = SDL_GetKeyName(native_event.key.key);
            self->key.code = native_event.key.key;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN: case SDL_EVENT_MOUSE_BUTTON_UP:
            self->type = EventType_MouseButton;
            self->mouse_button.pressed = native_event.button.down;
            self->mouse_button.double_click  = native_event.button.clicks >= 2;
            self->mouse_button.button = native_event.button.button;
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            self->type = EventType_MouseWheel;
            self->mouse_wheel.horizontal = native_event.wheel.x;
            self->mouse_wheel.vertical = native_event.wheel.y;
            break;
        case SDL_EVENT_MOUSE_MOTION:
            self->type = EventType_MouseMotion;
            self->mouse_motion.absolute = (vec2i_t){ .x = native_event.motion.x, .y = native_event.motion.y };
            self->mouse_motion.relative = (vec2i_t){ .x = native_event.motion.xrel, .y = native_event.motion.yrel };
            break;
        default:
            self->type = EventType_Unhandled;
            break;
    }
}
