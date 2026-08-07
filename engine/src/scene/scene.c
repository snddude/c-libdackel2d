#include "scene/scene.h"

#include "scene/components.h"

#include <stb_ds.h>

scene_t scene_create()
{
    scene_t scene;

    scene.entities = NULL;
    scene.ecs_world = ecs_init();

    register_components(scene.ecs_world);

    return scene;
}

void scene_destroy(scene_t *self)
{
    arrfree(self->entities);
    ecs_fini(self->ecs_world);
}

entity_t scene_create_entity(scene_t *self)
{
    entity_t entity = entity_create(self->ecs_world);
    arrput(self->entities, entity);

    return entity;
}

void scene_destroy_entity(scene_t *self, entity_t *entity)
{
    for (long int i = 0; i < arrlen(self->entities); i++)
        if (entity->id == self->entities[i].id)
        {
            arrdel(self->entities, i);
            entity_destroy(entity);
            break;
        }
}

void scene_render(scene_t *self, SDL_Renderer *renderer)
{
    // Requires implementation of renderer methods for
    // the colored rect and sprite components at least.
}
