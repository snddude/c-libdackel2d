#pragma once

#include "core/renderer.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void resource_manager_init(renderer_t *renderer_p);

SDL_Texture *load_texture(const char *path);
TTF_Font *load_font(const char *path, float size);
