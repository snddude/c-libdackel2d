#include "core/application.h"

#include "core/window.h"
#include "events/event.h"

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
    SDL_Event native_event;
    SDL_Renderer *renderer = window_get_renderer(application->ptr_main_window);

    window_set_visible(application->ptr_main_window, true);

    while (1)
    {
        while (SDL_PollEvent(&native_event))
        {
            if (native_event.type == SDL_EVENT_QUIT)
                goto End;

            Event event = event_create(native_event);

            // Dispatch event to application layers...
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // ...

        SDL_RenderPresent(renderer);
    }
End:
}

Window *application_get_main_window(Application *application)
{
    return application->ptr_main_window;
}
