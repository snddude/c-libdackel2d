#pragma once

#include "core/event.h"
#include "core/renderer.h"

typedef struct
{
	void (*on_attach)();
	void (*on_detach)();

	void (*process_event)(event_t *event);
	void (*process)(double delta);
	void (*render)(renderer_t *renderer);
} layer_t;

void layer_on_attach(layer_t *self);
void layer_on_detach(layer_t *self);

void layer_process_event(layer_t *self, event_t *event);
void layer_process(layer_t *self, double delta);
void layer_render(layer_t *self, renderer_t *renderer);
