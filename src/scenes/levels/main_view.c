#include "main_view.h"
#include "src/types/scene_types.h"
#include "src/types/state.h"
#include "src/logic/scene.h"
#include "src/components/font.h"
#include "src/components/win.h"

#define TITLE_TEXT "DB_LISTENER CONNECTED"

bool main_view_init(struct main_view_t* level) {
  return true;
}
static bool load(struct scene_t *scene, struct state_t *state) {
  struct main_view_t *local = (struct main_view_t *)scene->__internal;
  if (!label_init(&local->title, &state->font)) {
    SDL_LogError(1, "could not initialize title.\n");
    return false;
  }
  if (!label_set_text(&local->title, TITLE_TEXT, strlen(TITLE_TEXT))) {
    SDL_LogError(1, "could not set text for title.\n");
    return false;
  }
  SDL_Rect win_size = win_get_size(&state->win);
  SDL_Rect title_size = label_get_size(&local->title);
  (void)label_set_center_pos(&local->title, win_size.w / 2, title_size.h + 20);
  if (!scene_add_child(scene, label_get_render(&local->title))) {
    return false;
  }
  return true;
}
static bool unload(struct scene_t *scene, struct state_t *state) {
  struct main_view_t *local = (struct main_view_t *)scene->__internal;
  main_view_free(local);
  free(local);
  return true;
}
static bool update(struct scene_t *scene, struct state_t *state) {
  return true;
}
static bool event(struct scene_t *scene, struct state_t *state,
                  SDL_Event *event) {
  return true;
}
struct scene_t* main_view_prepare(struct main_view_t *s) {
  struct scene_t *result = scene_create();
  result->__internal = s;
  result->load = load;
  result->unload = unload;
  result->update = update;
  result->event = event;
  return result;
}
void main_view_free(struct main_view_t* level) {
  label_free(&level->title);
}

