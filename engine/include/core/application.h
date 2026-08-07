#pragma once

#include "core/window.h"
#include "core/layer.h"

#include <stddef.h>

typedef struct application
{
    size_t fps_limit;
    window_t main_window;
    Layer *layer_stack;
} application_t;

application_t application_create();
void application_destroy(application_t *self);

void application_run(application_t *self);

void application_push_layer(application_t *self, Layer layer);
Layer application_pop_layer(application_t *self);
