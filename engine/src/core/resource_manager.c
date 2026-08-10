#include <core/resource_manager.h>

#include <stb_ds.h>
#include <SDL3_image/SDL_image.h>

typedef struct
{
    const char *key;
    void *value;
} resource_manager_cache_t;

static SDL_Renderer *renderer = NULL;
static resource_manager_cache_t *cache = NULL;

void resource_manager_init(renderer_t *renderer_p)
{
    renderer = renderer_p->sdl_renderer_p;
}

SDL_Texture *load_texture(const char *path)
{
    if (hmgeti(cache, path) != -1)
        return hmget(cache, path);

    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    hmput(cache, path, (void *)texture);

    return texture;
}

TTF_Font *load_font(const char *path, float size)
{
    if (hmgeti(cache, path) != -1)
        return hmget(cache, path);

    TTF_Font *font = TTF_OpenFont(path, size);
    hmput(cache, path, (void *)font);

    return font;
}
