#ifndef SGF_WORLD_H
#define SGF_WORLD_H

#include "defs.h"
#include "src/types/entities/entity.h"
#include <SDL3/SDL_rect.h>
#include <stdbool.h>

struct world_t;
struct win_t;

/**
 * Initialize world with a given rect.
 *
 * @return True on success, False otherwise.
 */
bool world_init_with_rect(struct world_t *w, SDL_FRect rect) __nonnull((1));

/**
 * Initialize world with a given window.
 * The world's rect is set to the size of the given window.
 *
 * @return True on success, False otherwise.
 */
bool world_init_with_win(struct world_t *w, struct win_t *win)
    __nonnull((1, 2));

/**
 * Apply the properties of the world onto the given rect.
 *
 * @return The updated rect.
 */
SDL_FRect world_apply(const struct world_t *w, SDL_FRect rect) __nonnull((1));

/**
 * Apply the properties of the world onto the given Entity structure.
 * This function handles translating the Entity's coordinates to the world's
 * coordinates.
 *
 * @return The updated rect.
 */
SDL_FRect world_apply_to_entity(const struct world_t *w, struct entity_t ent)
    __nonnull((1));

/**
 * Check if the rect should be drawn.
 */
bool world_should_draw(const struct world_t *w, const SDL_Rect *render_rect,
                       const SDL_FRect *rect);

/**
 * Check if the entity should be drawn.
 */
bool world_should_draw_ent(const struct world_t *w, const SDL_Rect *render_rect,
                           const struct entity_t *ent);
#endif
