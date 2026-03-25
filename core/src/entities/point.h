/**
 * @file point.h
 * @brief Point entity functions.
 */

#ifndef SGF_POINT_H
#define SGF_POINT_H

#include "../types/base.h"
#include "../types/entity.h"
#include <stdbool.h>

struct point_t;

/**
 * @brief Configuration options for point initialization.
 */
struct point_options_t {
  /** @brief Initial world coordinates. */
  struct coordinate_t coord;
  /** @brief Initial projection offset. */
  struct coordinate_t proj;
  /** @brief Size of the point. */
  struct area_t size;
  /** @brief Point color. */
  SDL_Color color;
};

/**
 * @brief Initialize a point entity.
 *
 * If options is NULL, the point is zeroed out.
 *
 * @param[out] p Pointer to point to initialize.
 * @param[in] options Configuration options, or NULL for defaults.
 * @return true on success, false on failure.
 */
bool point_init(struct point_t *p, struct point_options_t *options);

/**
 * @brief Free point resources.
 *
 * @param[out] p Pointer to point to free.
 */
void point_free(struct point_t *p);

/**
 * @brief Get the render interface for this point.
 *
 * @param[in] p Pointer to the point.
 * @return render_t structure with render functions.
 */
struct render_t point_get_render(struct point_t *p);

#endif
