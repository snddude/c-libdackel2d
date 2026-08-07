#pragma once

#include "math/vector2.h"

#include <SDL3/SDL.h>
#include <stdbool.h>

#define WINDOW_FLAGS SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN

typedef struct
{
    SDL_Window *sdl_window_p;
    SDL_Renderer *sdl_renderer_p;
} window_t;

window_t window_create(const char *title, int width, int height);
void window_destroy(window_t *self);

bool window_get_visible(window_t *self);
void window_set_visible(window_t *self, bool value);

bool window_get_resizable(window_t *self);
void window_set_resizable(window_t *self, bool value);

bool window_get_fullscreen(window_t *self);
void window_set_fullscreen(window_t *self, bool value);

const char *window_get_title(window_t *self);
void window_set_title(window_t *self, const char *value);

Vector2 window_get_size(window_t *self);
void window_set_size(window_t *self, int width, int height);
