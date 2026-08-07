#pragma once

#include "core/window.h"
#include "core/layer.h"

#include <stddef.h>
#include <stdbool.h>

#define APPLICATION_INIT_FLAGS SDL_INIT_VIDEO

typedef struct application
{
    size_t fps_limit;
    window_t main_window;
    layer_t *layer_stack;
} application_t;

bool application_init(application_t *self);
void application_destroy(application_t *self);

void application_run(application_t *self);

void application_push_layer(application_t *self, layer_t layer);
layer_t application_pop_layer(application_t *self);
