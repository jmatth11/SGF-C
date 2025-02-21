#ifndef SGF_BASE_H
#define SGF_BASE_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <stdbool.h>
#include <stdint.h>

#include "deps/array_template/array_template.h"

struct base_t {
  void *parent;
  uint64_t id;
};


typedef bool(*render_fn)(struct base_t *obj, SDL_Renderer* ren);
typedef SDL_Rect(*collision_rect_fn)(struct base_t *obj);
typedef bool(*collision_fn)(struct base_t *obj, void* other);
typedef bool(*mouse_event_fn)(struct base_t *obj, SDL_Event *event);

// TODO maybe subscribe specifically for mouse events instead
// of doing a check on every character
struct events_t {
  struct base_t base;
  mouse_event_fn mouse_event;
};

struct collision_event_t {
  struct base_t base;
  collision_rect_fn collision_rect;
  collision_fn collision;
};

struct render_t {
  struct base_t base;
  render_fn render;
};

generate_array_template(base_obj, struct base_t)
generate_array_template(events, struct events_t)
generate_array_template(collision, struct collision_event_t)
generate_array_template(render, struct render_t)

#endif
