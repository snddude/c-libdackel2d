#include "test_layer.h"

#include <dackel2d.h>
#include <stdlib.h>

#define SPEED 128.0f

static Vector2 wish_vel;

static void on_attach()
{
    SDL_Log("Hello from test layer!");
}

static void on_detach()
{
    SDL_Log("Goodbye from test layer!");
}

static void process_event(event_t *event)
{
    switch (event->type)
    {
        case EventType_MouseButton:
            if (event->mouse_button.pressed)
            {
                SDL_Log("%d", event->mouse_button.button);
                event->handled = true;
            }
            break;
        case EventType_Key:
            if (!event->key.echo && event->key.pressed)
            {
                SDL_Log(event->key.label);
                event->handled = true;
            }
            break;
    }
}

static void process(double delta)
{
    Vector2 input = input_get_vector(KeyCode_A, KeyCode_D, KeyCode_S, KeyCode_W);
    vector2_normalize(&input);
    Vector2 velocity = vector2_multiply(input, delta * SPEED);

    wish_vel = vector2_add(wish_vel, velocity);
}

static void render(SDL_Renderer *renderer)
{
    SDL_FRect rect = {
        0.0f + wish_vel.x,
        0.0f + wish_vel.y,
        16.0f,
        16.0f
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

layer_t test_layer_create()
{
    return (layer_t){
        .on_attach = on_attach,
        .on_detach = on_detach,
        .process_event = process_event,
        .process = process,
        .render = render
    };
}
