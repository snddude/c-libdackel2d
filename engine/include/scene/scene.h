#pragma once

#include "scene/entity.h"

#include <SDL3/SDL.h>

typedef struct scene Scene;

Scene *scene_create();
void scene_destroy(Scene *scene);

Entity *scene_create_entity(Scene *scene);
void scene_destroy_entity(Scene *scene, Entity *entity);

void scene_process(Scene *scene, double delta);
void scene_render(Scene *scene, SDL_Renderer *renderer);
