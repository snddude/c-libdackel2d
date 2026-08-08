#include "test_layer.h"

#include <dackel2d.h>
#include <stdlib.h>

#define PLAYER_SPEED 128.0f

static scene_t game_scene;
static entity_t player;

static void on_attach()
{
    SDL_Log("Hello from test layer!");

    game_scene = scene_create();

    player = scene_create_entity(&game_scene);
    entity_add_component(&player, transform_t);
    entity_add_component(&player, renderable_t);
    entity_add_component(&player, colored_rect_t);

    renderable_t *player_renderable = entity_get_component(&player, renderable_t);
    player_renderable->visible = true;
    player_renderable->z_index = 0;

    transform_t *player_transform = entity_get_component(&player, transform_t);
    player_transform->rotation = 0.0f;
    player_transform->position = VECTOR2_ZERO;
    player_transform->scale = VECTOR2_ONE;

    colored_rect_t *player_visual = entity_get_component(&player, colored_rect_t);
    player_visual->size = (Vector2){16.0f, 16.0f};
    player_visual->color = (SDL_FColor){1.0f, 0.0f, 0.0f, 1.0f};
}

static void on_detach()
{
    SDL_Log("Goodbye from test layer!");
    entity_destroy(&player);
    scene_destroy(&game_scene);
}

static void process_event(event_t *event)
{
    switch (event->type)
    {
        case EventType_MouseButton:
            if (event->mouse_button.pressed)
            {
                SDL_Log("%d", event->mouse_button.button);
                event->handled = true;
            }
            break;
        case EventType_Key:
            if (!event->key.echo && event->key.pressed)
            {
                SDL_Log(event->key.label);
                event->handled = true;
            }
            break;
    }
}

static void process(double delta)
{
    Vector2 input = input_get_vector(KeyCode_A, KeyCode_D, KeyCode_S, KeyCode_W);
    vector2_normalize(&input);
    Vector2 velocity = vector2_multiply(input, delta * PLAYER_SPEED);

    transform_t *player_transform = entity_get_component(&player, transform_t);
    player_transform->position = vector2_add(player_transform->position, velocity);
}

static void render(renderer_t *renderer)
{
    scene_render(&game_scene, renderer);
}

layer_t test_layer_create()
{
    return (layer_t){
        .on_attach = on_attach,
        .on_detach = on_detach,
        .process_event = process_event,
        .process = process,
        .render = render
    };
}
