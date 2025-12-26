#ifndef SGF_WORLD_TYPES_H
#define SGF_WORLD_TYPES_H

#include <SDL3/SDL_rect.h>

/**
 * Structure to represent a world view.
 */
struct world_t {
  /* offset and size of the world. */
  SDL_FRect rect;
  /* Scale factor for everything in the world. */
  float scale;
};

#endif
