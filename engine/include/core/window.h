#pragma once

#include <SDL3/SDL.h>

typedef struct window Window;

Window *window_create();
Window *window_create(const char *title, int w, int h);
void window_destroy(Window *window);

bool window_is_visible(Window *window);
void window_set_visible(Window *window, bool is_visible);

const char *window_get_title(Window *window);
void *window_set_title(Window *window, const char *title);

void window_get_size(Window *window, int *w, int *h);
void window_set_size(Window *window, int w, int h);

bool window_get_resizable(Window *window);
void window_set_resizable(Window *window, bool is_resizable);

bool window_get_fullscreen(Window *window);
void window_set_fullscreen(Window *window, bool is_fullscreen);

SDL_Window *window_get_native(Window *window);
SDL_Renderer *window_get_renderer(Window *window);
