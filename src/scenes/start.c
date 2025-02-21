#include "start.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "src/components/button.h"
#include "src/logic/scene.h"

bool scene_one_init(struct scene_one_t *s) {
  if (!button_init(&s->start_btn, 1)) {
    return false;
  }
  if (!button_init(&s->exit_btn, 2)) {
    return false;
  }
  return true;
}

static bool load(struct scene_t *scene) {
  struct scene_one_t *local = (struct scene_one_t*)scene->__internal;
  // TODO add text to button
  local->start_btn.rect = (SDL_FRect){
    .h = 40,
    .w = 70,
    .x = 100,
    .y = 100,
  };
  local->start_btn.theme = (struct theme_t){
    .color = {.r=0x06, .g=0x66, .b=0xaa, .a=0xff},
  };
  local->exit_btn.rect = (SDL_FRect){
    .h = 40,
    .w = 70,
    .x = 100,
    .y = 160,
  };
  local->exit_btn.theme = (struct theme_t){
    .color = {.r=0x06, .g=0x66, .b=0xaa, .a=0xff},
  };
  if (!scene_add_child(scene, button_get_render(&local->start_btn))) {
    return false;
  }
  if (!scene_add_child(scene, button_get_render(&local->exit_btn))) {
    return false;
  }
  return true;
}

static bool unload(struct scene_t *scene) {
  struct scene_one_t *local = (struct scene_one_t*)scene->__internal;
  button_free(&local->start_btn);
  button_free(&local->exit_btn);
  free(local);
  return true;
}

static bool update(struct scene_t *scene, struct state_t *state) {

  return true;
}

static bool event(struct scene_t *scene, struct state_t *state, SDL_Event *event) {

  return true;
}

struct scene_t* scene_one_prepare(struct scene_one_t *s) {
  struct scene_t *result = scene_create();
  result->__internal = s;
  result->load = load;
  result->unload = unload;
  result->update = update;
  result->event = event;
  return result;
}

void scene_one_free(struct scene_one_t *s) {

}
