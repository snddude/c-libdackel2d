#include "core/window.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

#include "math/vector2.h"

typedef struct window
{
    SDL_Window *ptr_sdl_window;
    SDL_Renderer *ptr_sdl_renderer;

} Window;

Window *window_create(const char *title, int w, int h)
{
    Window *window = malloc(sizeof(Window));

    window->ptr_sdl_window = SDL_CreateWindow(title, w, h, SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN);
    if (window->ptr_sdl_window == NULL)
    {
        SDL_Log("Failed to create native window: %s", SDL_GetError());
        return NULL;
    }

    window->ptr_sdl_renderer = SDL_CreateRenderer(window->ptr_sdl_window, "vulkan");
    if (window->ptr_sdl_renderer == NULL)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return NULL;
    }

    return window;
}

void window_destroy(Window *window)
{
    SDL_DestroyRenderer(window->ptr_sdl_renderer);
    SDL_DestroyWindow(window->ptr_sdl_window);

    free(window);
}

bool window_is_visible(Window *window)
{
    return !SDL_GetWindowFlags(window->ptr_sdl_window) & SDL_WINDOW_HIDDEN;
}

void window_set_visible(Window *window, bool is_visible)
{
    is_visible ? SDL_ShowWindow(window->ptr_sdl_window) : SDL_HideWindow(window->ptr_sdl_window);
}

const char *window_get_title(Window *window)
{
    return SDL_GetWindowTitle(window->ptr_sdl_window);
}

void *window_set_title(Window *window, const char *title)
{
    SDL_SetWindowTitle(window->ptr_sdl_window, title);
}

Vector2 window_get_size(Window *window)
{
    int w, h;
    SDL_GetWindowSize(window->ptr_sdl_window, &w, &h);

    return (Vector2){(float)w, (float)h};
}

void window_set_size(Window *window, int w, int h)
{
    SDL_SetWindowSize(window->ptr_sdl_window, w, h);
}

bool window_get_resizable(Window *window)
{
    return SDL_GetWindowFlags(window->ptr_sdl_window) & SDL_WINDOW_RESIZABLE;
}

void window_set_resizable(Window *window, bool is_resizable)
{
    SDL_SetWindowResizable(window->ptr_sdl_window, is_resizable);
}

bool window_get_fullscreen(Window *window)
{
    return SDL_GetWindowFlags(window->ptr_sdl_window) & SDL_WINDOW_FULLSCREEN;
}

void window_set_fullscreen(Window *window, bool is_fullscreen)
{
    SDL_SetWindowFullscreen(window->ptr_sdl_window, is_fullscreen);
}

SDL_Window *window_get_native(Window *window)
{
    return window->ptr_sdl_window;
}

SDL_Renderer *window_get_renderer(Window *window)
{
    return window->ptr_sdl_renderer;
}
