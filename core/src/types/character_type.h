/**
 * @file character_type.h
 * @brief Character entity type definition.
 *
 * TODO: Implement character entity functionality.
 */

#ifndef SGF_CHARACTER_ENTITY_H
#define SGF_CHARACTER_ENTITY_H

#include "../types/base.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdint.h>

/**
 * @brief Character entity with health tracking.
 */
struct character_t {
  /** @brief Screen rectangle for rendering. */
  SDL_FRect rect;
  /** @brief Unique identifier for this character. */
  base_id id;
  /** @brief Current health points. */
  int32_t health;
  /** @brief Character color. */
  SDL_Color color;
};

#endif
