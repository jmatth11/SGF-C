#ifndef SGF_LOADING_ICON_TYPE_H
#define SGF_LOADING_ICON_TYPE_H

#include "SDL3/SDL_rect.h"
#include <SDL3/SDL_render.h>

struct loading_icon_t {
  SDL_Texture *texture;
  float rotation_speed;
  float angle;
  SDL_FRect rect;
  SDL_FRect background;
  SDL_Color background_color;
};

#endif
