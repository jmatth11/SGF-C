#ifndef GENERIC_BUTTON_TYPES_H
#define GENERIC_BUTTON_TYPES_H

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdint.h>

struct theme_t {
  SDL_Color color;
  // TODO add TTF
};

typedef void(*button_callback)(SDL_MouseButtonEvent *e, void* context);

struct button_t {
  void *context;
  uint32_t id;
  struct theme_t theme;
  SDL_FRect rect;
  button_callback onClick;
};

#endif
