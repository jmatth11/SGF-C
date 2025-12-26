#ifndef SGF_POINT_H
#define SGF_POINT_H

#include "src/types/base.h"
#include "src/types/entities/entity.h"
#include <stdbool.h>

struct point_t;

/**
 * Options for the Point's initialize function.
 */
struct point_options_t {
  struct coordinate_t coord;
  struct area_t size;
  float proj_z;
  SDL_Color color;
};

/**
 * Initialize point.
 * If options is NULL, the point is zeroed out.
 */
bool point_init(struct point_t *p, struct point_options_t *options);

/**
 * Free point.
 */
void point_free(struct point_t *p);

/**
 * Get the render vtable of the point.
 */
struct render_t point_get_render(struct point_t *p);

#endif
