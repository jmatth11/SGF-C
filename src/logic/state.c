#include "state.h"
#include "scene.h"
#include "src/components/win.h"
#include "src/types/scene_types.h"
#include "src/types/state.h"

bool state_init(struct state_t* s) {
  s->current_scene = NULL;
  return true;
}

bool state_switch_scene(struct state_t *s, struct scene_t *scene) {
  if (s->current_scene) {
    s->current_scene->unload(s->current_scene);
    scene_destroy(&s->current_scene);
  }
  s->current_scene = scene;
  if (s->current_scene) {
    s->current_scene->load(s->current_scene);
  }
  return true;
}

void state_free(struct state_t* s) {
  state_switch_scene(s, NULL);
  win_free(&s->win);
}
