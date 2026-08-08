#include "core/renderer.h"

#include "core/window.h"

#include <SDL3_image/SDL_image.h>
#include <stb_ds.h>

static SDL_Texture *rasterize_colored_rect(SDL_Renderer *renderer, colored_rect_t *rect)
{
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        rect->size.x,
        rect->size.y
    );

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(
        renderer,
        rect->color.r,
        rect->color.g,
        rect->color.b,
        rect->color.a
    );
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    return texture;
}

bool renderer_init(renderer_t *self, window_t *window)
{
    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(window->sdl_window_p, RENDERER_INIT_FLAGS);
    if (sdl_renderer == NULL)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    self->sdl_renderer_p = sdl_renderer;
    self->cache = NULL;

    return true;
}

void renderer_destroy(renderer_t *self)
{
    for (long int i = 0; i < hmlen(self->cache); i++)
        SDL_DestroyTexture(self->cache[i].value);

    hmfree(self->cache);
    SDL_DestroyRenderer(self->sdl_renderer_p);
}

void renderer_draw_colored_rect(renderer_t *self, transform_t *transform, colored_rect_t *rect)
{
    bool cached = hmgeti(self->cache, (void *)rect) != -1;
    SDL_Texture *rect_texture = cached ? hmget(self->cache, (void *)rect) : rasterize_colored_rect(self->sdl_renderer_p, rect);
    SDL_FRect destination = {
        .x = transform->position.x,
        .y = transform->position.y,
        .w = rect->size.x * transform->scale.x,
        .h = rect->size.y * transform->scale.y
    };

    if (!cached)
        hmput(self->cache, (void *)rect, rect_texture);

    SDL_RenderTextureRotated(
        self->sdl_renderer_p,
        rect_texture,
        NULL,
        &destination,
        transform->rotation,
        NULL,
        SDL_FLIP_NONE
    );
}

void renderer_draw_sprite(renderer_t *self, transform_t *transform, sprite_t *sprite)
{
    float tw, th;
    SDL_GetTextureSize(sprite->texture, &tw, &th);

    SDL_FRect destination = {
        .x = transform->position.x,
        .y = transform->position.y,
        .w = tw * transform->scale.x,
        .h = th * transform->scale.y
    };

    SDL_RenderTextureRotated(
        self->sdl_renderer_p,
        sprite->texture,
        NULL,
        &destination,
        transform->rotation,
        NULL,
        SDL_FLIP_NONE
    );
}
