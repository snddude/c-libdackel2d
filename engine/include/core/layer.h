#pragma once

#include <SDL3/SDL.h>
#include "core/event.h"

typedef struct
{
	void (*on_attach)();
	void (*on_detach)();

	void (*process_event)(Event *event);
	void (*process)(double delta);
	void (*render)(SDL_Renderer *renderer);

} layer_t;

void layer_on_attach(layer_t *self);
void layer_on_detach(layer_t *self);

void layer_process_event(layer_t *self, Event *event);
void layer_process(layer_t *self, double delta);
void layer_render(layer_t *self, SDL_Renderer *renderer);
