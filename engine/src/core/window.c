#include "core/window.h"

window_t window_create(const char *title, int width, int height)
{
    window_t self;

    self.sdl_window_p = SDL_CreateWindow(title, width, height, WINDOW_FLAGS);
    if (self.sdl_window_p == NULL)
    {
        SDL_Log("Failed to create native self: %s", SDL_GetError());
        return (window_t){0};
    }

    self.sdl_renderer_p = SDL_CreateRenderer(self.sdl_window_p, "vulkan");
    if (self.sdl_renderer_p == NULL)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return (window_t){0};
    }

    return self;
}

void window_destroy(window_t *self)
{
    SDL_DestroyRenderer(self->sdl_renderer_p);
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
