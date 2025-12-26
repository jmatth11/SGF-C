#ifndef SGF_BASE_COMPONENT_H
#define SGF_BASE_COMPONENT_H

#include <SDL3/SDL_rect.h>

struct component_t;

typedef SDL_FRect (*component_get_rect_fn)(struct component_t *);

struct component_t {
  void *__internal;
  component_get_rect_fn get_rect;
};

#endif
