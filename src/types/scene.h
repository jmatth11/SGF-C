#ifndef SGF_SCENE_H
#define SGF_SCENE_H

#include "SDL3/SDL_events.h"
#include <stdbool.h>

struct scene_t;
struct state_t;

typedef bool(*update_fn)(struct scene_t *scene, struct state_t *state);
typedef bool(*event_fn)(struct scene_t *scene, struct state_t *state, SDL_Event *event);

struct scene_t {
  update_fn update;
  event_fn event;
};

#endif
