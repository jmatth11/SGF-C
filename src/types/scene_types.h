#ifndef SGF_SCENE_TYPES_H
#define SGF_SCENE_TYPES_H

#include "SDL3/SDL_events.h"
#include <stdbool.h>

#include "src/types/base.h"

struct scene_t;
struct state_t;
struct world_t;

typedef bool (*load_fn)(struct scene_t *scene, struct state_t *state);
typedef bool (*update_fn)(struct scene_t *scene, struct state_t *state,
                          double deltatime);
typedef bool (*event_fn)(struct scene_t *scene, struct state_t *state,
                         SDL_Event *event);
typedef bool (*unload_fn)(struct scene_t *scene, struct state_t *state);

struct scene_t {
  void *__internal;
  render_array children;
  events_array events;
  collision_array collisions;
  struct events_t *focused_el;
  struct world_t *world;

  load_fn load;
  update_fn update;
  event_fn event;
  unload_fn unload;
};

#endif
