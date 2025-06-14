#include "start.h"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include <stdbool.h>

#include "src/components/button.h"
#include "src/components/font.h"
#include "src/components/loading_icon.h"
#include "src/components/text_input.h"
#include "src/components/toast.h"
#include "src/components/win.h"
#include "src/logic/scene.h"
#include "src/logic/state.h"
#include "src/logic/user_data.h"
#include "src/scenes/levels/main_view.h"
#include "src/scenes/main_menu/gui.h"
#include "src/types/state.h"
#include "src/types/user_data.h"

bool scene_one_init(struct scene_one_t *s) {
  (void)s;
  return true;
}

static bool load(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  local->user_data = user_data_create();
  if (local->user_data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "user data failed to initialize\n");
    return false;
  }
  state->user_data = local->user_data;
  local->toast_manager = toast_manager_create();
  if (local->toast_manager == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error creating toast manager.\n");
    return false;
  }
  local->toast_manager->parent_scene = scene;
  local->toast_manager->font = &state->font;
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
  if (!toast_manager_update(local->toast_manager, NULL)) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "toast manager update failed.\n");
  }
  if (local->loading) {
    enum user_data_status_options status = user_data_get_status(local->user_data);
    switch (status) {
      case UDS_CONNECTED: {
        struct main_view_t *next_scene = malloc(sizeof(struct main_view_t));
        if (!state_switch_scene(state, main_view_prepare(next_scene))) {
          SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error switching to main scene.\n");
          return false;
        }
        break;
      }
      case UDS_ERROR: {
        // TODO display error
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "UDS_ERROR occurred\n");
        break;
      }
      default:{
        break;
      }
    }
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
  toast_manager_destroy(&s->toast_manager);
  loading_icon_free(&s->loading_icon);
  label_free(&s->title);
  button_free(&s->start_btn);
  button_free(&s->exit_btn);
}
