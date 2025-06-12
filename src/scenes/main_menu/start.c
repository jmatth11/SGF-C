#include "start.h"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include <stdbool.h>

#include "src/components/button.h"
#include "src/components/font.h"
#include "src/components/loading_icon.h"
#include "src/components/text_input.h"
#include "src/components/win.h"
#include "src/logic/scene.h"
#include "src/scenes/main_menu/gui.h"
#include "src/types/state.h"
#include "websocket.h"

bool scene_one_init(struct scene_one_t *s) {
  (void)s;
  return true;
}

static bool load(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  (void)ws_client_init(&local->user_data.client);
  local->user_data.data_url = NULL;
  local->loading = false;
  local->loading_shown = false;
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
  struct scene_one_t* local = (struct scene_one_t*)scene->__internal;
  if (local->loading) {
    if (!local->loading_shown) {
      SDL_Log("adding loading icon to screen");
      local->loading_shown = true;
      if (!scene_add_child(scene, loading_icon_get_render(&local->loading_icon))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to add loading render_t");
        return false;
      }
    }
    loading_icon_update(&local->loading_icon);
  }
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
  loading_icon_free(&s->loading_icon);
  label_free(&s->title);
  button_free(&s->start_btn);
  button_free(&s->exit_btn);
}
