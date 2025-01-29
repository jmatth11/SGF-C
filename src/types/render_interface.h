#ifndef GENERIC_RENDER_INTERFACE_TYPE_H
#define GENERIC_RENDER_INTERFACE_TYPE_H

#include <SDL3/SDL_render.h>

typedef void(*render_callback)(SDL_Renderer *ren, void*context);

struct render_interface {
  void* context;
  render_callback render;
};

#endif
