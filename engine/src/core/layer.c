#include "core/layer.h"

void layer_on_attach(layer_t *self)
{
    if (self->on_attach_pfn != NULL)
        self->on_attach_pfn();
}

void layer_on_detach(layer_t *self)
{
    if (self->on_detach_pfn != NULL)
        self->on_detach_pfn();
}

void layer_process_event(layer_t *self, event_t *event)
{
    if (self->process_event_pfn != NULL)
        self->process_event_pfn(event);
}

void layer_process(layer_t *self, double delta)
{
    if (self->process_pfn != NULL)
        self->process_pfn(delta);
}

void layer_render(layer_t *self, SDL_Renderer *renderer)
{
    if (self->render_pfn != NULL)
        self->render_pfn(renderer);
}
