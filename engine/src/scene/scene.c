#include "scene/scene.h"

#include "scene/components.h"
#include "scene/entity.h"

#include <stb_ds.h>
#include <flecs.h>
#include <stdlib.h>

typedef struct scene {
    Entity **entities;
    ecs_world_t *ecs_world;

} Scene;

Scene *scene_create()
{
    Scene *scene = malloc(sizeof(Scene));
    scene->entities = NULL;

    scene->ecs_world = ecs_init();
    register_components(scene->ecs_world);

    return scene;
}

void scene_destroy(Scene *scene)
{
    arrfree(scene->entities);
    ecs_fini(scene->ecs_world);

    free(scene);
}

Entity *scene_create_entity(Scene *scene)
{
    Entity *entity = entity_create(scene->ecs_world);
    arrput(scene->entities, entity);

    return entity;
}

void scene_destroy_entity(Scene *scene, Entity *entity)
{
    for (long int i = 0; i < arrlen(scene->entities); i++)
        if (entity->id == scene->entities[i]->id)
        {
            arrdel(scene->entities, i);
            entity_destroy(entity);
            break;
        }
}
