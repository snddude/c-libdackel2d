#pragma once

#include <flecs.h>
#include <SDL3/SDL.h>
#include <vec2.h>
#include <stdbool.h>

typedef struct
{
    const char *name;
} name_tag_t;

typedef struct
{
    float rotation;
    vec2f_t position;
    vec2f_t scale;
} transform_t;

typedef struct
{
    int z_index;
    bool visible;
} renderable_t;

typedef struct
{
    vec2f_t size;
    SDL_FColor color;
} colored_rect_t;

typedef struct
{
    SDL_Texture *texture;
    SDL_FColor modulate;
} sprite_t;

extern ECS_COMPONENT_DECLARE(name_tag_t);
extern ECS_COMPONENT_DECLARE(transform_t);
extern ECS_COMPONENT_DECLARE(renderable_t);
extern ECS_COMPONENT_DECLARE(colored_rect_t);
extern ECS_COMPONENT_DECLARE(sprite_t);

void register_components(ecs_world_t *ecs_world);
