#include "test_layer.h"

#include <dackel2d.h>
#include <stdlib.h>

static void on_attach()
{
    SDL_Log("Hello from test layer!");
}

static void on_detach()
{
    SDL_Log("Goodbye from test layer!");
}

static void process_event(Event *event)
{
    switch (event->type)
    {
        case EventType_MouseMotion:
            EventMouseMotion *mm = (EventMouseMotion *)event->super_type;
            SDL_Log("[INFO] x: %.2f y: %.2f", mm->absolute.x, mm->absolute.y);
            event->handled = true;
            break;
        case EventType_Key:
            EventKey *k = (EventKey *)event->super_type;

            if (!k->echo && k->pressed)
            {
                SDL_Log(k->label);
                event->handled = true;
            }
    }
}

static void process(double delta)
{
    // SDL_Log("[INFO] delta time: %f", delta);
}

static void render(SDL_Renderer *renderer)
{
    SDL_FRect rect = {8.0f, 8.0f, 64.0f, 64.0f};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

Layer test_layer_create()
{
    return (Layer){
        .on_attach = on_attach,
        .on_detach = on_detach,
        .process_event = process_event,
        .process = process,
        .render = render
    };
}
