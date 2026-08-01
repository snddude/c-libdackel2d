#pragma once

#include <flecs.h>

#define entity_has_component(entity, component) \
    ecs_has(entity->ptr_ecs_world, entity->id, component)

#define entity_get_component(entity, component, value) \
    while(!entity_has_component(entity, component)) \
        { value = ecs_get(entity->ptr_ecs_world, entity->id, component); }

#define entity_add_component(entity, component) \
    while(!entity_has_component(entity, component)) \
        { ecs_add(entity->ptr_ecs_world, entity->id, component); }

#define entity_remove_component(entity, component) \
    while(entity_has_component(entity, component)) \
        { ecs_remove(entity->ptr_ecs_world, entity->id, component); }

typedef struct entity {
    ecs_entity_t id;
    ecs_world_t *ptr_ecs_world;

} Entity;

Entity *entity_create(ecs_world_t *ptr_ecs_world);
void entity_destroy(Entity *entity);
