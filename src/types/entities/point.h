#ifndef SGF_POINT_TYPE_H
#define SGF_POINT_TYPE_H

#include "entity.h"
#include "src/types/base.h"

/**
 * Graphical point in space.
 */
struct point_t {
  base_id id;
  struct entity_t entity;
  SDL_Color color;
};

#endif
