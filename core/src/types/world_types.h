/**
 * @file world_types.h
 * @brief World view type definition.
 */

#ifndef SGF_WORLD_TYPES_H
#define SGF_WORLD_TYPES_H

#include <SDL3/SDL_rect.h>

/**
 * @brief Structure representing a 2D world view with 3D projection.
 *
 * The world defines how 3D coordinates are projected to 2D screen space
 * and provides frustum culling bounds.
 */
struct world_t {
  /** @brief Offset and size of the world view. */
  SDL_FRect rect;
  /** @brief Scale factor applied to everything in the world. Default 1.0. */
  float scale;
  /** @brief Focal length for perspective projection. Default 1.0. */
  float focal_length;
  /** @brief Objects closer than this Z value are not rendered. Default 0.001. */
  float close_cutoff;
  /** @brief Objects farther than this Z value are not rendered. Default 25.0. */
  float far_cutoff;
};

#endif
