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
  s->exit_clicked = false;
  return true;
}

static bool load(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  local->text_input.id = 12;
  SDL_Rect win_size = win_get_size(&state->win);
  SDL_Rect title_size = label_get_size(&local->title);
  // ignoring return
  (void)label_set_center_pos(&local->title, win_size.w / 2, title_size.h + 20);
  if (!scene_add_child(scene, label_get_render(&local->title))) {
    return false;
  }
  if (!text_input_init(&local->text_input, &state->font,
                       (SDL_FRect){
                           .x = ((double)win_size.w / 2) - 60,
                           .y = title_size.h + 60,
                           .w = -1, // default to 120
                           .h = -1, // default to font size
                       })) {
    SDL_LogError(1, "Text input failed to initialize.\n");
    return false;
  }
  if (!scene_add_child(scene, text_input_get_render(&local->text_input))) {
    SDL_LogError(1, "text input could not be added to scene.\n");
    return false;
  }
  if (!scene_add_event_listener(scene,
                                text_input_get_event(&local->text_input))) {
    SDL_LogError(1, "text input event could not be added to scene.\n");
    return false;
  }
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
  (void)scene;
  (void)event;
  if (exit_clicked) {
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
  label_free(&s->title);
  button_free(&s->start_btn);
  button_free(&s->exit_btn);
}
