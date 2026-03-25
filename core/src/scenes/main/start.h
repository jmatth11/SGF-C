/**
 * @file start.h
 * @brief Main scene definitions.
 */

#ifndef SCENE_ONE_START_H
#define SCENE_ONE_START_H

#include "../../types/entity.h"
#include "../../types/point.h"
#include "../../types/world_types.h"
#include <stdbool.h>

/**
 * @brief Scene one data structure.
 */
struct scene_one_t {
  /** @brief World context for 3D projection. */
  struct world_t world;
  /** @brief Array of points to render. */
  struct point_t points[8];
  /** @brief Current rotation angle. */
  double angle;
  /** @brief Z velocity for animation. */
  double dz;
};

/**
 * @brief Initialize scene one.
 *
 * @param[out] s Scene data to initialize.
 * @return true on success, false on failure.
 */
bool scene_one_init(struct scene_one_t *s);

/**
 * @brief Prepare and configure the scene.
 *
 * @param[out] s Scene data.
 * @return Configured scene structure, or NULL on failure.
 */
struct scene_t *scene_one_prepare(struct scene_one_t *s);

/**
 * @brief Free scene one resources.
 *
 * @param[out] s Scene data to free.
 */
void scene_one_free(struct scene_one_t *s);

#endif
