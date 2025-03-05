#include "scene.h"
#include <stdlib.h>
#include <stdio.h>
#include "src/logic/base.h"
#include "src/types/scene_types.h"

struct scene_t* scene_create() {
  struct scene_t* local = (struct scene_t*)malloc(
    sizeof(struct scene_t)
  );
  local->__internal = NULL;
  if (!render_array_init(&local->children, 5)) {
    fprintf(stderr, "failed to initialize scene render array.\n");
    return NULL;
  }
  if (!events_array_init(&local->events, 1)) {
    fprintf(stderr, "failed to initialize scene render array.\n");
    return NULL;
  }
  if (!collision_array_init(&local->collisions, 1)) {
    fprintf(stderr, "failed to initialize scene render array.\n");
    return NULL;
  }
  return local;
}

bool scene_add_child(struct scene_t* scene, struct render_t ren) {
  return render_array_insert(&scene->children, ren);
}
bool scene_add_event_listener(struct scene_t* scene, struct events_t e) {
  return events_array_insert(&scene->events, e);
}
bool scene_add_collision_listener(struct scene_t* scene, struct collision_event_t c) {
  return collision_array_insert(&scene->collisions, c);
}

bool scene_check_events(struct scene_t* scene, SDL_Event *e) {
  bool result = true;
  size_t event_len = scene->events.len;
  if (event_len > 0) {
    for (size_t i = 0; i < event_len; ++i) {
      struct events_t local_e = scene->events.events_data[i];
      switch (e->type) {
        case SDL_EVENT_MOUSE_MOTION: SDL_FALLTHROUGH;
        case SDL_EVENT_MOUSE_BUTTON_UP: SDL_FALLTHROUGH;
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
          result = base_handle_mouse_event(&local_e, e);
          break;
        }
      }
    }
  }
  return result;
}

void scene_destroy(struct scene_t **scene) {
  struct scene_t *local = *scene;
  render_array_free(&local->children);
  events_array_free(&local->events);
  collision_array_free(&local->collisions);
  local->__internal = NULL;
  free(local);
  (*scene) = NULL;
}
