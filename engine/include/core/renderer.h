#pragma once

#include "scene/components.h"

#include <SDL3/SDL.h>
#include <stdbool.h>

#define RENDERER_INIT_FLAGS "vulkan"

typedef struct 
{
    ecs_entity_t key;
    SDL_Texture *value;
} renderer_cache_t;

typedef struct
{
    SDL_Renderer *sdl_renderer_p;
    renderer_cache_t *cache;
} renderer_t;

typedef struct window window_t;

bool renderer_init(renderer_t *self, window_t *window);
void renderer_destroy(renderer_t *self);

void renderer_draw_colored_rect(renderer_t *self, transform_t *transform, renderable_t *renderable, colored_rect_t *rect);
void renderer_draw_sprite(renderer_t *self, transform_t *transform, renderable_t *renderable, sprite_t *sprite);
