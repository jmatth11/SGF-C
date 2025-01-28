#ifndef GENERIC_WIN_TYPES_H
#define GENERIC_WIN_TYPES_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

struct win_t {
  SDL_Window *win;
  SDL_Renderer *ren;
  SDL_Color background;
};

#endif
