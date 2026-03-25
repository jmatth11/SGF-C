#include "platform.h"
#include <SDL3/SDL_log.h>

bool platform_create_main(platform_ctx_t *ctx, const char *title, int w, int h) {
    SDL_Window *local_win = NULL;
    SDL_Renderer *local_ren = NULL;
    if (!SDL_CreateWindowAndRenderer(title, w, h, SDL_WINDOW_HIGH_PIXEL_DENSITY,
                                     &local_win, &local_ren)) {
        SDL_LogError(1, "error: couldn't create window/renderer -- %s",
                     SDL_GetError());
        return false;
    }
    if (local_ren == NULL || local_win == NULL) {
        SDL_LogCritical(1, "window or renderer could not be initialised: %s\n",
                        SDL_GetError());
        return false;
    }
    ctx->ren = local_ren;
    ctx->win = local_win;
    return true;
}

SDL_Rect platform_get_size(platform_ctx_t *ctx) {
    SDL_Rect result = {
        .x = 0,
        .y = 0,
        .w = 0,
        .h = 0,
    };
    if (!SDL_GetWindowSize(ctx->win, &result.w, &result.h)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "failed to get window size: %s\n", SDL_GetError());
    }
    return result;
}

void platform_free(platform_ctx_t *ctx) {
    SDL_DestroyRenderer(ctx->ren);
    SDL_DestroyWindow(ctx->win);
}
