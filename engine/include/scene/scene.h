#pragma once

#include "scene/entity.h"

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct scene {
    entity_t *entities;
    ecs_world_t *ecs_world;
} scene_t;

scene_t scene_create();
void scene_destroy(scene_t *self);

entity_t scene_create_entity(scene_t *self);
void scene_destroy_entity(scene_t *self, entity_t *entity);

void scene_render(scene_t *self, SDL_Renderer *renderer);
