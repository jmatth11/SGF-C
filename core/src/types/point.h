/**
 * @file point.h
 * @brief Point type definition.
 */

#ifndef SGF_POINT_TYPE_H
#define SGF_POINT_TYPE_H

#include "entity.h"
#include "../types/base.h"

/**
 * @brief Graphical point rendered in 3D world space.
 */
struct point_t {
  /** @brief Unique identifier for this point. */
  base_id id;
  /** @brief Entity data for position and projection. */
  struct entity_t entity;
  /** @brief Fill color of the point. */
  SDL_Color color;
};

#endif
