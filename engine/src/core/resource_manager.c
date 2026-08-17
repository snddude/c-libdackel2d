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
    slog_info("Initializing resource manager...");

    renderer = renderer_p->sdl_renderer_p;

    slog_info("Resource manager initialized successfully!");
}

void resource_manager_destroy()
{
    slog_info("Destroying resource manager...");

    slog_info("Clearing resource manager's cache...");
    for (long int i = 0; i < hmlen(cache); i++)
    {
        resource_handle_t key = cache[i].key;
        void *value = cache[i].value;

        switch (key.type)
        {
            case ResourceType_Texture:
                SDL_DestroyTexture((SDL_Texture *)value);
                slog_info("Destroyed texture '%s'", key.texture.path);
                break;
            case ResourceType_Font:
                TTF_CloseFont((TTF_Font *)value);
                slog_info("Destroyed font '%s' with size %d", key.font.path, key.font.size);
                break;
        }
    }

    hmfree(cache);

    slog_info("Resource manager destroyed successfully!");
}

SDL_Texture *load_texture(const char *path)
{
    resource_handle_t handle = {
        .type = ResourceType_Texture,
        .texture.path = path
    };

    if (hmgeti(cache, handle) != -1)
        return (SDL_Texture *)hmget(cache, handle);

    slog_info("Loading texture '%s' for the first time...", path);
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL)
    {
        slog_error("Failed to load texture! %s", SDL_GetError());
        return NULL;
    }

    hmput(cache, handle, (void *)texture);
    slog_info("Texture '%s' cached successfully!", path);

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

    slog_info("Loading font '%s' with size %.2f for the first time...", path, size);
    TTF_Font *font = TTF_OpenFont(path, size);
    if (font == NULL)
    {
        slog_error("Failed to load font! %s", SDL_GetError());
        return NULL;
    }

    hmput(cache, handle, (void *)font);
    slog_info("Font '%s' with size %.2f cached successfully!", path, size);

    return font;
}
