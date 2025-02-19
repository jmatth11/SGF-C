#ifndef SGF_BASE_H
#define SGF_BASE_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <stdbool.h>
#include <stdint.h>

struct base_t;

typedef bool(*render_fn)(struct base_t *obj, SDL_Renderer* ren);
typedef SDL_Rect(*collision_rect_fn)(struct base_t *obj);
typedef bool(*collision_fn)(struct base_t *obj, void* other);
typedef bool(*mouse_event_fn)(struct base_t *obj, SDL_Event *event);

// TODO maybe subscribe specifically for mouse events instead
// of doing a check on every character
struct events_t {
  mouse_event_fn mouse_event;
};

struct collision_event_t {
  collision_rect_fn collision_rect;
  collision_fn collision;
};

struct base_t {
  void *parent;
  uint64_t id;
  struct events_t events;
  struct collision_event_t collision;
  render_fn render;
};


#endif
