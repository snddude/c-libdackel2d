#pragma once

#include <SDL3/SDL.h>
#include "events/event.h"

typedef struct layer
{
	void (*on_attach)();
	void (*on_detach)();

	bool (*process_event)(Event event);
	void (*process)(double delta);
	void (*render)(SDL_Renderer *renderer);

} Layer;

void layer_on_attach(Layer layer);
void layer_on_detach(Layer layer);

bool layer_process_event(Layer layer, Event event);
void layer_process(Layer layer, double delta);
void layer_render(Layer layer, SDL_Renderer *renderer);
