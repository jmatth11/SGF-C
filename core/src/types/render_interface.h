#ifndef GENERIC_RENDER_INTERFACE_TYPE_H
#define GENERIC_RENDER_INTERFACE_TYPE_H

#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_pixels.h"
#include <SDL3/SDL_render.h>

struct render_attributes_t {
  SDL_Color color;
  SDL_BlendMode blend_mode;
};

#endif
