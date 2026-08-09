#include "scene/scene.h"

#include "scene/components.h"

#include <stb_ds.h>

static int compare_z_index(ecs_entity_t e1  __attribute__((unused)), const void *v1, ecs_entity_t e2  __attribute__((unused)), const void *v2)
{
    const renderable_t *d1 = v1;
    const renderable_t *d2 = v2;
    return d1->z_index > d2->z_index;
}

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

void scene_render(scene_t *self, renderer_t *renderer)
{
    ecs_query_t *q = ecs_query(self->ecs_world, 
    {
        .terms = {{ .id = ecs_id(renderable_t) }},
        .order_by = ecs_id(renderable_t),
        .order_by_callback = compare_z_index
    });
    ecs_iter_t it = ecs_query_iter(self->ecs_world, q);

    while (ecs_query_next(&it))
        for (int i = 0; i < it.count; i++)
        {
            entity_t entity = {
                .id = it.entities[i],
                .ecs_world_p = self->ecs_world
            };

            if (!entity_get_component(&entity, renderable_t)->visible)
                continue;

            if (!entity_has_component(&entity, transform_t))
                continue;

            if (entity_has_component(&entity, colored_rect_t))
                renderer_draw_colored_rect(
                    renderer,
                    entity_get_component(&entity, transform_t), 
                    entity_get_component(&entity, colored_rect_t)
                );

            if (entity_has_component(&entity, sprite_t))
                renderer_draw_sprite(
                    renderer,
                    entity_get_component(&entity, transform_t), 
                    entity_get_component(&entity, sprite_t)
                );
        }

    ecs_query_fini(q);
}
