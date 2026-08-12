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
    entity_t obstacle = scene_create_entity(&game_scene);
    entity_t enemy = scene_create_entity(&game_scene);

    entity_add_component(&player, renderable_t);
    renderable_t *player_renderable = entity_get_component(&player, renderable_t);
    player_renderable->visible = true;
    player_renderable->z_index = 0;

    entity_add_component(&obstacle, renderable_t);
    renderable_t *obstacle_renderable = entity_get_component(&obstacle, renderable_t);
    obstacle_renderable->visible = true;
    obstacle_renderable->z_index = 1;

    entity_add_component(&enemy, renderable_t);
    renderable_t *enemy_renderable = entity_get_component(&enemy, renderable_t);
    enemy_renderable->visible = true;
    enemy_renderable->z_index = -5;

    entity_add_component(&player, transform_t);
    transform_t *player_transform = entity_get_component(&player, transform_t);
    player_transform->rotation = 0.0f;
    player_transform->position = VECTOR2_ZERO;
    player_transform->scale = vector2_multiply(VECTOR2_ONE, 2.0f);

    entity_add_component(&obstacle, transform_t);
    transform_t *obstacle_transform = entity_get_component(&obstacle, transform_t);
    obstacle_transform->rotation = 0.0f;
    obstacle_transform->position = VECTOR2_ZERO;
    obstacle_transform->scale = VECTOR2_ONE;

    entity_add_component(&enemy, transform_t);
    transform_t *enemy_transform = entity_get_component(&enemy, transform_t);
    enemy_transform->rotation = 0.0f;
    enemy_transform->position = (Vector2){ 32.0f, 32.0f };
    enemy_transform->scale = vector2_multiply(VECTOR2_ONE, 3.0f);

    entity_add_component(&player, sprite_t);
    sprite_t *player_visual = entity_get_component(&player, sprite_t);
    player_visual->modulate = (SDL_FColor){ 1.0f, 1.0f, 1.0f, 1.0f };
    player_visual->texture = load_texture("assets/sprites/Heart.png");

    entity_add_component(&obstacle, colored_rect_t);
    colored_rect_t *obstacle_visual = entity_get_component(&obstacle, colored_rect_t);
    obstacle_visual->size = (Vector2){32.0f, 32.0f};
    obstacle_visual->color = (SDL_FColor){1.0f, 0.0f, 1.0f, 1.0f};

    entity_add_component(&enemy, sprite_t);
    sprite_t *enemy_visual = entity_get_component(&enemy, sprite_t);
    enemy_visual->modulate = (SDL_FColor){ 1.0f, 1.0f, 1.0f, 1.0f };
    enemy_visual->texture = load_texture("assets/sprites/Mr.SpookyScary.png");
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
        default:
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
        .on_attach_pfn = on_attach,
        .on_detach_pfn = on_detach,
        .process_event_pfn = process_event,
        .process_pfn = process,
        .render_pfn = render
    };
}
