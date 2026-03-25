/**
 * @file entity.h
 * @brief Entity type definitions for world objects.
 */

#ifndef SGF_BASE_ENTITY
#define SGF_BASE_ENTITY

#include <SDL3/SDL_rect.h>
#include <stdbool.h>

/**
 * @brief 3D coordinate in world space.
 *
 * Coordinates should be normalized to the -1.0 to 1.0 range for consistent
 * behavior with the world projection system.
 */
struct coordinate_t {
  /** @brief X coordinate. */
  float x;
  /** @brief Y coordinate. */
  float y;
  /** @brief Z coordinate (depth). */
  float z;
};

/**
 * @brief Zeroed coordinate at the origin.
 */
#define ZERO_COORD (struct coordinate_t){0, 0, 0}

/**
 * @brief 2D size/area structure.
 */
struct area_t {
  /** @brief Width. */
  float w;
  /** @brief Height. */
  float h;
};

/**
 * @brief Zeroed area.
 */
#define ZERO_AREA (struct area_t){0, 0}

/**
 * @brief Entity for world rendering with 3D positioning.
 *
 * An entity exists in 3D space with a base coordinate and a projection
 * offset. The projection Z determines the on-screen size via perspective
 * scaling when adjust_size is enabled.
 */
struct entity_t {
  /** @brief Base coordinate in world space. */
  struct coordinate_t coord;
  /** @brief Projection offset coordinate. Z affects on-screen size. */
  struct coordinate_t proj;
  /** @brief Size of the entity. */
  struct area_t size;
  /** @brief If true, entity size scales based on projection Z. */
  bool adjust_size;
};

/**
 * @brief Zeroed entity.
 */
#define ZERO_ENTITY                                                            \
  (struct entity_t){                                                           \
      .coord = (struct coordinate_t){0, 0, 0},                                 \
      .proj = (struct coordinate_t){0, 0, 0},                                  \
      .size = (struct area_t){0, 0},                                           \
      .adjust_size = false,                                                    \
  }

#endif
