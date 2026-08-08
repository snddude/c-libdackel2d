#include "core/layer.h"

void layer_on_attach(layer_t *self)
{
    if (self->on_attach != NULL)
        self->on_attach();
}

void layer_on_detach(layer_t *self)
{
    if (self->on_detach != NULL)
        self->on_detach();
}

void layer_process_event(layer_t *self, event_t *event)
{
    if (self->process_event != NULL)
        self->process_event(event);
}

void layer_process(layer_t *self, double delta)
{
    if (self->process != NULL)
        self->process(delta);
}

void layer_render(layer_t *self, renderer_t *renderer)
{
    if (self->render != NULL)
        self->render(renderer);
}
