#include "core/application.h"

#include "core/event.h"

#include <SDL3/SDL.h>
#include <stb_ds.h>
#include <stdlib.h>

typedef struct application
{
    Window *ptr_main_window;
    Layer *layer_stack;

} Application;

Application *application_create()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return NULL;
    }

    Application *application = malloc(sizeof(Application));
    application->ptr_main_window = window_create("Engine", 640, 480);
    application->layer_stack = NULL;

    return application;
}

void application_destroy(Application *application)
{
    window_destroy(application->ptr_main_window);

    for (long int i = 0; i < arrlen(application->layer_stack); i++)
    {
        Layer layer = arrpop(application->layer_stack);
        layer_on_detach(layer);
    }

    arrfree(application->layer_stack);   
    free(application);

    SDL_Quit();
}

void application_run(Application *application)
{
    double delta;

    Uint64 last = 0;
	Uint64 now = SDL_GetPerformanceCounter();
    SDL_Event native_event;
    SDL_Renderer *renderer = window_get_renderer(application->ptr_main_window);

    window_set_visible(application->ptr_main_window, true);

    while (1)
    {
		last = now;
		now = SDL_GetPerformanceCounter();
		delta = (double)(now - last) / (double)SDL_GetPerformanceFrequency();

        size_t layer_count = arrlen(application->layer_stack);

        while (SDL_PollEvent(&native_event))
        {
            if (native_event.type == SDL_EVENT_QUIT)
                goto End;

            Event event = event_create(native_event);

            for (int i = layer_count - 1; i >= 0; i--)
            {
                layer_process_event(application->layer_stack[i], &event);

                if (event.handled)
                    break;
            }
        }

        for (size_t i = 0; i < layer_count; i++)
            layer_process(application->layer_stack[i], delta);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < layer_count; i++)
            layer_render(application->layer_stack[i], renderer);

        SDL_RenderPresent(renderer);
    }
End:
}

void application_push_layer(Application *application, Layer layer)
{
    arrput(application->layer_stack, layer);
    layer_on_attach(layer);
}

void application_pop_layer(Application *application)
{
    Layer layer = arrpop(application->layer_stack);
    layer_on_detach(layer);
}

void application_pop_layer_at(Application *application, size_t index)
{
    Layer layer = application->layer_stack[index];
    layer_on_detach(layer);

    arrdel(application->layer_stack, index);
}

Window *application_get_main_window(Application *application)
{
    return application->ptr_main_window;
}
