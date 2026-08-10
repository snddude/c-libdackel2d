#include "core/application.h"

#include "core/event.h"
#include "core/resource_manager.h"

#include <SDL3/SDL.h>
#include <stb_ds.h>

bool application_init(application_t *self)
{
    if (!SDL_Init(APPLICATION_INIT_FLAGS))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window_t window;
    if (!window_init(&window, "Engine", 640, 480))
        return false;

    resource_manager_init(&window.renderer);

    self->fps_limit = 0;
    self->main_window = window;
    self->layer_stack = NULL;

    return true;
}

void application_destroy(application_t *self)
{
    window_destroy(&(self->main_window));

    for (long int i = 0; i < arrlen(self->layer_stack); i++)
        application_pop_layer(self);

    arrfree(self->layer_stack);   
    SDL_Quit();
}

void application_run(application_t *self)
{
    double delta;

    Uint64 last = 0;
	Uint64 now = SDL_GetPerformanceCounter();
    SDL_Event native_event;

    window_set_visible(&(self->main_window), true);
    renderer_t *main_window_renderer = &self->main_window.renderer;

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

            event_t event = event_create(native_event);

            for (int i = layer_count - 1; i >= 0; i--)
            {
                layer_process_event(&self->layer_stack[i], &event);

                if (event.handled)
                    break;
            }
        }

        for (size_t i = 0; i < layer_count; i++)
            layer_process(&self->layer_stack[i], delta);

        renderer_begin(main_window_renderer);

        for (size_t i = 0; i < layer_count; i++)
            layer_render(&self->layer_stack[i], main_window_renderer);

        renderer_end(main_window_renderer);

        if (self->fps_limit > 0)
            SDL_Delay(1000 / self->fps_limit);
    }
End:
}

void application_push_layer(application_t *self, layer_t layer)
{
    arrput(self->layer_stack, layer);
    layer_on_attach(&layer);
}

layer_t application_pop_layer(application_t *self)
{
    layer_t layer = arrpop(self->layer_stack);
    layer_on_detach(&layer);

    return layer;
}
