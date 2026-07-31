#include "scene/entity.h"

#include "scene/components.h"

#include <flecs.h>
#include <stdlib.h>

Entity *entity_create(ecs_world_t *ptr_ecs_world)
{
    Entity *entity = malloc(sizeof(Entity));

    entity->id = ecs_new(ptr_ecs_world);
    entity->ptr_ecs_world = ptr_ecs_world;

    return entity;
}

void entity_destroy(Entity *entity)
{
    ecs_delete(entity->ptr_ecs_world, entity->id);
    free(entity);
}
