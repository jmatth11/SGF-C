/**
 * @file render.h
 * @brief Render helper functions.
 */

#ifndef SGF_RENDER_HELPERS_H
#define SGF_RENDER_HELPERS_H

#include <stdbool.h>

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>

#include "defs.h"

struct render_attributes_t;
struct base_t;
struct render_ctx_t;

/**
 * @brief Validate render function arguments.
 *
 * Checks that obj, obj->parent, and ctx->ren are not NULL.
 * Does not check ctx->world because some scenes don't need a world.
 *
 * @param[in] obj Base object being rendered.
 * @param[in] ctx Render context.
 * @return true if arguments are valid, false otherwise.
 */
bool render_check_args(struct base_t *obj, struct render_ctx_t *ctx);

/**
 * @brief Set the renderer blend mode.
 *
 * @param[in] ren SDL renderer.
 * @param[in] mode Blend mode to set.
 * @param[out] old If not NULL, receives the previous blend mode.
 * @return true on success, false on failure.
 */
bool render_set_blendmode(SDL_Renderer *ren, SDL_BlendMode mode,
                          SDL_BlendMode *old) __nonnull((1));

/**
 * @brief Render a transparent filled rectangle.
 *
 * Uses SDL_BLENDMODE_BLEND to achieve transparency.
 *
 * @param[in] ren SDL renderer.
 * @param[in] color Fill color (alpha channel used for transparency).
 * @param[in] rect Destination rectangle.
 * @return true on success, false on failure.
 */
bool render_transparent_fill_rect(SDL_Renderer *ren, SDL_Color color,
                                  SDL_FRect *rect) __nonnull((1));

/**
 * @brief Get current renderer attributes.
 *
 * @param[in] ren SDL renderer.
 * @param[out] out Receives the current color and blend mode.
 * @return true on success, false on failure.
 */
bool render_get_attributes(SDL_Renderer *ren, struct render_attributes_t *out);

/**
 * @brief Set renderer attributes.
 *
 * @param[in] ren SDL renderer.
 * @param[in] att Attributes to set.
 * @return true on success, false on failure.
 */
bool render_set_attributes(SDL_Renderer *ren, struct render_attributes_t *att);

#endif
