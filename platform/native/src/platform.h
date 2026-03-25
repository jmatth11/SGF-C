#ifndef PLATFORM_NATIVE_H
#define PLATFORM_NATIVE_H

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>

/**
 * Platform context structure.
 * Handles window and renderer.
 */
typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
} platform_ctx_t;

/**
 * Create main window and renderer.
 *
 * @param ctx The platform context struct.
 * @param title The title for the window.
 * @param w The width.
 * @param h The height.
 * @return True on success, false otherwise.
 */
bool platform_create_main(platform_ctx_t *ctx, const char *title, int w, int h);

/**
 * Get the size of the window.
 *
 * @param ctx The platform context.
 * @return The window size rect.
 */
SDL_Rect platform_get_size(platform_ctx_t *ctx);

/**
 * Free the internals of the platform context.
 *
 * @param ctx The platform context.
 */
void platform_free(platform_ctx_t *ctx);

#endif
