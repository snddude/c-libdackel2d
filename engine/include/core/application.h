#pragma once

#include "core/window.h"
#include "core/layer.h"

typedef struct application Application;

Application *application_create();
void application_destroy(Application *application);

void application_run(Application *application);

void application_push_layer(Application *application, Layer layer);
void application_pop_layer(Application *application);
void application_pop_layer_at(Application *application, size_t index);

Window *application_get_main_window(Application *application);
