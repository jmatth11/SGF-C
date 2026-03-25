/**
 * @file world.h
 * @brief World view and 3D projection functions.
 */

#ifndef SGF_WORLD_H
#define SGF_WORLD_H

#include "defs.h"
#include "../types/entity.h"
#include <SDL3/SDL_rect.h>
#include <stdbool.h>

struct world_t;
struct win_t;

/**
 * @brief Initialize world with explicit bounds.
 *
 * @param[out] w World to initialize.
 * @param[in] rect Bounds of the world.
 * @return true on success, false on failure.
 */
bool world_init_with_rect(struct world_t *w, SDL_FRect rect) __nonnull((1));

/**
 * @brief Initialize world from window size.
 *
 * @param[out] w World to initialize.
 * @param[in] win Window to get size from.
 * @return true on success, false on failure.
 */
bool world_init_with_win(struct world_t *w, struct win_t *win)
    __nonnull((1, 2));

/**
 * @brief Apply world transformation to a rectangle.
 *
 * @param[in] w World to apply.
 * @param[in] rect Rectangle to transform.
 * @return Transformed rectangle.
 */
SDL_FRect world_apply(const struct world_t *w, SDL_FRect rect) __nonnull((1));

/**
 * @brief Transform an entity to screen coordinates.
 *
 * Handles 3D projection, perspective scaling, and world offset.
 *
 * @param[in] w World context.
 * @param[in] ent Entity to transform.
 * @return Screen rectangle, or zeroed rect if outside cutoff bounds.
 */
SDL_FRect world_apply_to_entity(const struct world_t *w, struct entity_t ent)
    __nonnull((1));

/**
 * @brief Check if a rectangle should be drawn.
 *
 * @param[in] w World context.
 * @param[in] render_rect Current render viewport.
 * @param[in] rect Rectangle to check.
 * @return true if visible, false if culled.
 */
bool world_should_draw(const struct world_t *w, const SDL_Rect *render_rect,
                       const SDL_FRect *rect);

/**
 * @brief Check if an entity should be drawn.
 *
 * @param[in] w World context.
 * @param[in] render_rect Current render viewport.
 * @param[in] ent Entity to check.
 * @return true if visible, false if culled.
 */
bool world_should_draw_ent(const struct world_t *w, const SDL_Rect *render_rect,
                           const struct entity_t *ent);
#endif
