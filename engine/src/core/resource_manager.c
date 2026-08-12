#include <core/resource_manager.h>

#include "logger/logger.h"

#include <stb_ds.h>
#include <SDL3_image/SDL_image.h>

typedef struct
{
    enum
    {
        ResourceType_Texture,
        ResourceType_Font,
    } type;
    union
    {
        struct { const char *path; } texture;
        struct { const char *path; float size; } font;
    };   
} resource_handle_t;

typedef struct
{
    resource_handle_t key;
    void *value;
} resource_cache_t;

static SDL_Renderer *renderer = NULL;
static resource_cache_t *cache = NULL;

void resource_manager_init(renderer_t *renderer_p)
{
    renderer = renderer_p->sdl_renderer_p;
}

void resource_manager_destroy()
{
    for (long int i = 0; i < hmlen(cache); i++)
    {
        resource_handle_t key = cache[i].key;
        void *value = cache[i].value;

        switch (key.type)
        {
            case ResourceType_Texture:
                SDL_DestroyTexture((SDL_Texture *)value);
                break;
            case ResourceType_Font:
                TTF_CloseFont((TTF_Font *)value);
                break;
        }
    }

    hmfree(cache);
}

SDL_Texture *load_texture(const char *path)
{
    resource_handle_t handle = {
        .type = ResourceType_Texture,
        .texture.path = path
    };

    if (hmgeti(cache, handle) != -1)
        return (SDL_Texture *)hmget(cache, handle);

    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL)
    {
        log_error("Failed to load texture! %s", SDL_GetError());
        return NULL;
    }

    hmput(cache, handle, (void *)texture);
    return texture;
}

TTF_Font *load_font(const char *path, float size)
{
    resource_handle_t handle = {
        .type = ResourceType_Font,
        .font.path = path,
        .font.size = size
    };

    if (hmgeti(cache, handle) != -1)
        return (TTF_Font *)hmget(cache, handle);

    TTF_Font *font = TTF_OpenFont(path, size);
    if (font == NULL)
    {
        log_error("Failed to load font! %s", SDL_GetError());
        return NULL;
    }

    hmput(cache, handle, (void *)font);
    return font;
}
