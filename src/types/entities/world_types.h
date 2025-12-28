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
  /* Focal length to use. Defaults to 1. */
  float focal_length;
  /**
   * The Z projection close cutoff.
   * This removes the object from view if the Z axis is too close to the camera.
   * Defaults to 0.001.
   */
  float close_cutoff;
  /**
   * The Z projection far cutoff.
   * This removes the object from view if the Z axis is too far from the camera.
   * Defaults to 25.
   */
  float far_cutoff;
};

#endif
