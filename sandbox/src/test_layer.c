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

    transform_t *player_transform = entity_get_component(&player, transform_t);
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

static void render(SDL_Renderer *renderer)
{
    transform_t *player_transform = entity_get_component(&player, transform_t);
    colored_rect_t *player_visual = entity_get_component(&player, colored_rect_t);

    SDL_FRect rect = {
        player_transform->position.x,
        player_transform->position.y,
        player_visual->size.x * player_transform->scale.x,
        player_visual->size.y * player_transform->scale.y,
    };

    SDL_SetRenderDrawColorFloat(renderer, player_visual->color.r, player_visual->color.g, player_visual->color.b, player_visual->color.a);
    SDL_RenderFillRect(renderer, &rect);
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
