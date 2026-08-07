#include "core/application.h"

#include "core/event.h"

#include <SDL3/SDL.h>
#include <stb_ds.h>

application_t application_create()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return (application_t){0};
    }

    application_t app;
    app.main_window = window_create("Engine", 640, 480);
    app.layer_stack = NULL;

    return app;
}

void application_destroy(application_t *self)
{
    window_destroy(&(self->main_window));

    for (long int i = 0; i < arrlen(self->layer_stack); i++)
    {
        Layer layer = arrpop(self->layer_stack);
        layer_on_detach(layer);
    }

    arrfree(self->layer_stack);   
    SDL_Quit();
}

void application_run(application_t *self)
{
    double delta;

    Uint64 last = 0;
	Uint64 now = SDL_GetPerformanceCounter();
    SDL_Event native_event;
    SDL_Renderer *renderer = self->main_window.sdl_renderer_p;

    window_set_visible(&(self->main_window), true);

    while (1)
    {
		last = now;
		now = SDL_GetPerformanceCounter();
		delta = (double)(now - last) / (double)SDL_GetPerformanceFrequency();

        size_t layer_count = arrlen(self->layer_stack);

        while (SDL_PollEvent(&native_event))
        {
            if (native_event.type == SDL_EVENT_QUIT)
                goto End;

            Event event = event_create(native_event);

            for (int i = layer_count - 1; i >= 0; i--)
            {
                layer_process_event(self->layer_stack[i], &event);

                if (event.handled)
                    break;
            }
        }

        for (size_t i = 0; i < layer_count; i++)
            layer_process(self->layer_stack[i], delta);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < layer_count; i++)
            layer_render(self->layer_stack[i], renderer);

        SDL_RenderPresent(renderer);
    }
End:
}

void application_push_layer(application_t *self, Layer layer)
{
    arrput(self->layer_stack, layer);
    layer_on_attach(layer);
}

void application_pop_layer(application_t *self)
{
    Layer layer = arrpop(self->layer_stack);
    layer_on_detach(layer);
}

void application_pop_layer_at(application_t *self, size_t index)
{
    Layer layer = self->layer_stack[index];
    layer_on_detach(layer);

    arrdel(self->layer_stack, index);
}
