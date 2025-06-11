#include "start.h"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include <stdbool.h>

#include "src/components/button.h"
#include "src/components/font.h"
#include "src/components/text_input.h"
#include "src/components/win.h"
#include "src/logic/scene.h"
#include "src/scenes/main_menu/gui.h"
#include "src/types/state.h"

#define start_text "start"
#define exit_text "exit"
#define title_text "Jumper"

bool scene_one_init(struct scene_one_t *s) {
  s->user_data.data_url = NULL;
  return true;
}

static bool load(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  local->exit_clicked = false;
  if (!setup_gui(scene, state)) {
    return false;
  }
  return true;
}

static bool unload(struct scene_t *scene, struct state_t *state) {
  (void)state;
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  scene_one_free(local);
  free(local);
  return true;
}

static bool update(struct scene_t *scene, struct state_t *state) {
  (void)scene;
  (void)state;
  return true;
}

static bool event(struct scene_t *scene, struct state_t *state,
                  SDL_Event *event) {
  (void)event;
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  if (local->exit_clicked) {
    state->app_state = SDL_APP_SUCCESS;
  }
  return true;
}

struct scene_t *scene_one_prepare(struct scene_one_t *s) {
  struct scene_t *result = scene_create();
  result->__internal = s;
  result->load = load;
  result->unload = unload;
  result->update = update;
  result->event = event;
  return result;
}

void scene_one_free(struct scene_one_t *s) {
  // TODO maybe free s->user_data.data_url
  label_free(&s->title);
  button_free(&s->start_btn);
  button_free(&s->exit_btn);
}
