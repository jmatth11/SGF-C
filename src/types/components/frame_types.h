#ifndef SGF_FRAME_TYPE_H
#define SGF_FRAME_TYPE_H

#include "src/types/base.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

struct frame_t {
  base_id id;
  SDL_FRect rect;
  SDL_Color color;
};

#endif
