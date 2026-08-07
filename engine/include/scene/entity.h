#pragma once

#include <flecs.h>

#define entity_has_component(self, component) \
    ecs_has((self)->ecs_world_p, (self)->id, (component))

#define entity_get_component(self, component) \
    ecs_get((self)->ecs_world_p, (self)->id, (component))

#define entity_add_component(self, component) \
    while(!entity_has_component((self), (component))) \
        { ecs_add((self)->ecs_world_p, (self)->id, (component)); }

#define entity_remove_component(self, component) \
    while(entity_has_component((self), (component))) \
        { ecs_remove((self)->ecs_world_p, (self)->id, (component)); }

typedef struct 
{
    ecs_entity_t id;
    ecs_world_t *ecs_world_p;
} entity_t;

entity_t entity_create(ecs_world_t *ecs_world_p);
void entity_destroy(entity_t *self);
