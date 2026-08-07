#include "scene/components.h"

ECS_COMPONENT_DECLARE(name_tag_t);
ECS_COMPONENT_DECLARE(transform_t);
ECS_COMPONENT_DECLARE(renderable_t);
ECS_COMPONENT_DECLARE(colored_rect_t);
ECS_COMPONENT_DECLARE(sprite_t);

void register_components(ecs_world_t *ecs_world)
{
    ECS_COMPONENT_DEFINE(ecs_world, name_tag_t);
    ECS_COMPONENT_DEFINE(ecs_world, transform_t);
    ECS_COMPONENT_DEFINE(ecs_world, renderable_t);
    ECS_COMPONENT_DEFINE(ecs_world, colored_rect_t);
    ECS_COMPONENT_DEFINE(ecs_world, sprite_t);
}
