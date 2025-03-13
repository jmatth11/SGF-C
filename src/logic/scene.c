#include "scene.h"
#include "src/logic/base.h"
#include "src/types/scene_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL_log.h>

struct scene_t *scene_create() {
  struct scene_t *local = (struct scene_t *)malloc(sizeof(struct scene_t));
  local->focused_el = NULL;
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

bool scene_add_child(struct scene_t *scene, struct render_t ren) {
  return render_array_insert(&scene->children, ren);
}
bool scene_add_event_listener(struct scene_t *scene, struct events_t e) {
  return events_array_insert(&scene->events, e);
}
bool scene_add_collision_listener(struct scene_t *scene,
                                  struct collision_event_t c) {
  return collision_array_insert(&scene->collisions, c);
}

static void debug_event(struct events_t *obj) {
  fprintf(stdout, "base ID = %lu\n", obj->base.id);
  fprintf(stdout, "focus_event is null %s\n", obj->focus_event == NULL ? "true" : "false");
  fprintf(stdout, "unfocus_event is null %s\n", obj->unfocus_event == NULL ? "true" : "false");
  fprintf(stdout, "point_in_rect is null %s\n", obj->pointInRect == NULL ? "true" : "false");
  fprintf(stdout, "rect_in_rect is null %s\n", obj->rectInRect == NULL ? "true" : "false");
  fprintf(stdout, "mouse_event is null %s\n", obj->mouse_event == NULL ? "true" : "false");
  fprintf(stdout, "text_event is null %s\n", obj->text_event == NULL ? "true" : "false");
  fflush(stdout);
}

bool scene_check_events(struct scene_t *scene, SDL_Event *e) {
  bool result = true;
  size_t event_len = scene->events.len;
  bool change_focus = false;
  struct events_t *focused_el = NULL;
  if (event_len > 0) {
    for (size_t i = 0; i < event_len; ++i) {
      struct events_t *local_e = &scene->events.events_data[i];
      switch (e->type) {
      case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        change_focus = true;
        SDL_FALLTHROUGH;
      }
      case SDL_EVENT_MOUSE_BUTTON_UP:
        SDL_FALLTHROUGH;
      case SDL_EVENT_MOUSE_MOTION: {
        result = base_handle_mouse_event(local_e, e, &focused_el);
        break;
      }
      case SDL_EVENT_KEY_UP:
        SDL_FALLTHROUGH;
      case SDL_EVENT_KEY_DOWN:
        SDL_FALLTHROUGH;
      case SDL_EVENT_TEXT_EDITING:
        SDL_FALLTHROUGH;
      case SDL_EVENT_TEXT_INPUT: {
        if (scene->focused_el != NULL && scene->focused_el == local_e) {
          result = base_handle_keyboard_event(scene->focused_el, e);
        }
        break;
      }
      }
    }
  }
  if (change_focus) {
    // unfocus
    if (scene->focused_el != NULL && scene->focused_el->unfocus_event != NULL) {
      scene->focused_el->unfocus_event(&scene->focused_el->base, e);
    }
    scene->focused_el = focused_el;
    // focus
    if (scene->focused_el != NULL && scene->focused_el->focus_event != NULL) {
      scene->focused_el->focus_event(&scene->focused_el->base, e);
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
  local->focused_el = NULL;
  free(local);
  (*scene) = NULL;
}
