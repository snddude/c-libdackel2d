#include "core/window.h"

#include "logger/logger.h"

bool window_init(window_t *self, const char *title, int width, int height)
{
    SDL_Window *sdl_window = SDL_CreateWindow(title, width, height, WINDOW_INIT_FLAGS);
    if (sdl_window == NULL)
    {
        slog_error("Failed to create native window: %s", SDL_GetError());
        return false;
    }

    self->sdl_window_p = sdl_window;

    renderer_t renderer;
    if (!renderer_init(&renderer, self))
        slog_error("Failed to create window renderer: %s", SDL_GetError());

    self->renderer = renderer;

    return true;
}

void window_destroy(window_t *self)
{
    renderer_destroy(&self->renderer);
    SDL_DestroyWindow(self->sdl_window_p);
}

bool window_get_visible(window_t *self)
{
    return (!SDL_GetWindowFlags(self->sdl_window_p)) & SDL_WINDOW_HIDDEN;
}

void window_set_visible(window_t *self, bool value)
{
    value ? SDL_ShowWindow(self->sdl_window_p) : SDL_HideWindow(self->sdl_window_p);
}

bool window_get_resizable(window_t *self)
{
    return SDL_GetWindowFlags(self->sdl_window_p) & SDL_WINDOW_RESIZABLE;
}

void window_set_resizable(window_t *self, bool value)
{
    SDL_SetWindowResizable(self->sdl_window_p, value);
}

bool window_get_fullscreen(window_t *self)
{
    return SDL_GetWindowFlags(self->sdl_window_p) & SDL_WINDOW_FULLSCREEN;
}

void window_set_fullscreen(window_t *self, bool value)
{
    SDL_SetWindowFullscreen(self->sdl_window_p, value);
}

const char *window_get_title(window_t *self)
{
    return SDL_GetWindowTitle(self->sdl_window_p);
}

void window_set_title(window_t *self, const char *value)
{
    SDL_SetWindowTitle(self->sdl_window_p, value);
}

Vector2 window_get_size(window_t *self)
{
    int w, h;
    SDL_GetWindowSize(self->sdl_window_p, &w, &h);

    return (Vector2){(float)w, (float)h};
}

void window_set_size(window_t *self, int width, int height)
{
    SDL_SetWindowSize(self->sdl_window_p, width, height);
}
