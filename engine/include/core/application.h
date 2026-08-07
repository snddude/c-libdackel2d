#pragma once

#include "core/window.h"
#include "core/layer.h"

typedef struct application
{
    window_t main_window;
    Layer *layer_stack;
} application_t;

application_t application_create();
void application_destroy(application_t *self);

void application_run(application_t *self);

void application_push_layer(application_t *self, Layer layer);
void application_pop_layer(application_t *self);
void application_pop_layer_at(application_t *self, size_t index);
