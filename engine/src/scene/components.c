#include "scene/components.h"

#include <flecs.h>

ECS_COMPONENT_DECLARE(NameTag);
ECS_COMPONENT_DECLARE(Transform);
ECS_COMPONENT_DECLARE(Renderable);
ECS_COMPONENT_DECLARE(ColoredRect);
ECS_COMPONENT_DECLARE(Sprite);

void register_components(ecs_world_t *ecs_world)
{
    ECS_COMPONENT_DEFINE(ecs_world, NameTag);
    ECS_COMPONENT_DEFINE(ecs_world, Transform);
    ECS_COMPONENT_DEFINE(ecs_world, Renderable);
    ECS_COMPONENT_DEFINE(ecs_world, ColoredRect);
    ECS_COMPONENT_DEFINE(ecs_world, Sprite);
}
