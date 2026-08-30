#include "scene/entity.h"

entity_t entity_create(ecs_world_t *ecs_world_p)
{
    return (entity_t) {
        .id = ecs_new(ecs_world_p),
        .ecs_world_p = ecs_world_p
    };
}

void entity_destroy(entity_t *self)
{
    ecs_delete(self->ecs_world_p, self->id);
}
