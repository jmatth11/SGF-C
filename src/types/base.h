#ifndef SGF_BASE_H
#define SGF_BASE_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <stdbool.h>
#include <stdint.h>

#include "array_template.h"

typedef uint64_t base_id;

struct base_t {
  void *parent;
  base_id id;
};

typedef bool (*render_fn)(struct base_t *obj, SDL_Renderer *ren);
typedef SDL_Rect (*collision_rect_fn)(struct base_t *obj);
typedef bool (*collision_fn)(struct base_t *obj, void *other);
typedef bool (*mouse_event_fn)(struct base_t *obj, SDL_Event *event);
typedef bool (*point_check_fn)(struct base_t *b, SDL_FPoint p);
typedef bool (*rect_check_fn)(struct base_t *b, SDL_FRect r);
typedef bool (*text_event_fn)(struct base_t *b, SDL_Event *event);
typedef bool (*focus_event_fn)(struct base_t *b, SDL_Event *e);
typedef bool (*unfocus_event_fn)(struct base_t *b, SDL_Event *e);

// TODO maybe subscribe specifically for mouse events instead
// of doing a check on every character
struct events_t {
  struct base_t base;
  point_check_fn pointInRect;
  rect_check_fn rectInRect;
  mouse_event_fn mouse_event;
  text_event_fn text_event;
  focus_event_fn focus_event;
  unfocus_event_fn unfocus_event;
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
