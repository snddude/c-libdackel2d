#include "core/layer.h"

#include <SDL3/SDL.h>
#include "events/event.h"

void layer_on_attach(Layer *layer)
{
    if (layer->on_attach != NULL)
        layer->on_attach();
}

void layer_on_detach(Layer *layer)
{
    if (layer->on_detach != NULL)
        layer->on_detach();
}

bool layer_process_event(Layer *layer, Event event)
{
    if (layer->process_event != NULL)
        return layer->process_event(event);

    return false;
}

void layer_process(Layer *layer, double delta)
{
    if (layer->process != NULL)
        layer->process(delta);
}

void layer_render(Layer *layer, SDL_Renderer *renderer)
{
    if (layer->render != NULL)
        layer->render(renderer);
}
