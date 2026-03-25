/**
 * @file frame_types.h
 * @brief Frame type definition.
 */

#ifndef SGF_FRAME_TYPE_H
#define SGF_FRAME_TYPE_H

#include "../types/base.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

/**
 * @brief Simple colored rectangle frame.
 */
struct frame_t {
  /** @brief Unique identifier for this frame. */
  base_id id;
  /** @brief Position and size of the frame. */
  SDL_FRect rect;
  /** @brief Fill color of the frame. */
  SDL_Color color;
};

#endif
