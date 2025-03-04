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
  if (!init_render_array(&local->children, 5)) {
    fprintf(stderr, "failed to initialize scene render array.\n");
    return NULL;
  }
  if (!init_events_array(&local->events, 1)) {
    fprintf(stderr, "failed to initialize scene render array.\n");
    return NULL;
  }
  if (!init_collision_array(&local->collisions, 1)) {
    fprintf(stderr, "failed to initialize scene render array.\n");
    return NULL;
  }
  return local;
}

bool scene_add_child(struct scene_t* scene, struct render_t ren) {
  return insert_render_array(&scene->children, ren);
}
bool scene_add_event_listener(struct scene_t* scene, struct events_t e) {
  return insert_events_array(&scene->events, e);
}
bool scene_add_collision_listener(struct scene_t* scene, struct collision_event_t c) {
  return insert_collision_array(&scene->collisions, c);
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
  free_render_array(&local->children);
  free_events_array(&local->events);
  free_collision_array(&local->collisions);
  local->__internal = NULL;
  free(local);
  (*scene) = NULL;
}
