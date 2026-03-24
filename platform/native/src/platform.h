#ifndef PLATFORM_NATIVE_H
#define PLATFORM_NATIVE_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
} platform_ctx_t;

bool platform_create_main(platform_ctx_t *ctx, const char *title, int w, int h);
SDL_Rect platform_get_size(platform_ctx_t *ctx);
void platform_free(platform_ctx_t *ctx);

#endif
