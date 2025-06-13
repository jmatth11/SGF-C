#ifndef SGF_CHARACTER_ENTITY_H
#define SGF_CHARACTER_ENTITY_H

#include "src/types/base.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdint.h>

struct character_t {
  SDL_FRect rect;
  base_id id;
  int32_t health;
  SDL_Color color;
};

#endif
