#pragma once

#include "math/vector2.h"

#include <flecs.h>
#include <SDL3/SDL.h>

typedef struct name_tag
{
    const char *name;

} NameTag;

typedef struct transform
{
    float rotation;
    Vector2 position;
    Vector2 scale;

} Transform;

typedef struct renderable
{
    int z_index;
    bool visible;

} Renderable;

typedef struct colored_rect
{
    Vector2 size;
    SDL_FColor color;

} ColoredRect;

typedef struct sprite
{
    SDL_Texture *texture;
    SDL_FColor modulate;

} Sprite;

extern ECS_COMPONENT_DECLARE(NameTag);
extern ECS_COMPONENT_DECLARE(Transform);
extern ECS_COMPONENT_DECLARE(Renderable);
extern ECS_COMPONENT_DECLARE(ColoredRect);
extern ECS_COMPONENT_DECLARE(Sprite);

void register_components(ecs_world_t *ecs_world);
