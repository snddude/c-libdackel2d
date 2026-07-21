#include "core/application.h"
#include "core/window.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

typedef struct application
{
    Window *ptr_main_window;

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

    return application;
}

void application_destroy(Application *application)
{
    window_destroy(application->ptr_main_window);
    free(application);

    SDL_Quit();
}

void application_run(Application *application)
{
    bool running = true;

    SDL_Event event;
    SDL_Renderer *renderer = window_get_renderer(application->ptr_main_window);

    window_set_visible(application->ptr_main_window, true);

    while (running)
    {
        while (SDL_PollEvent(&event))
            running = event.type != SDL_EVENT_QUIT;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // ...

        SDL_RenderPresent(renderer);
    }
}
