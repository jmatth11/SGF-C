#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include "SDL3/SDL_events.h"
#include "src/logic/scene.h"
#include "src/types/base.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include "SDL3_ttf/SDL_ttf.h"

#include "src/scenes/main_menu/start.h"
#include "src/types/scene_types.h"
#include "src/components/button.h"
#include "src/logic/state.h"
#include "src/types/components/button_types.h"
#include "src/types/state.h"
#include "src/components/win.h"
#include "src/types/win_types.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_LogTrace(2, "app initialization.\n");
  SDL_SetAppMetadata("Simple App", "1.0", "com.example.jmatth11");
  SDL_LogTrace(2, "init video.\n");
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_LogTrace(2, "init TTF.\n");
  if (!TTF_Init()) {
    SDL_Log("Couldn't initialize SDL_TTF: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  struct state_t *s = malloc(sizeof(struct state_t));
  SDL_LogTrace(2, "init state.\n");
  if (!state_init(s)) {
    SDL_Log("state failed to initialize");
    return SDL_APP_FAILURE;
  }
  *appstate = s;
  SDL_LogTrace(2, "setup scene one.\n");
  struct scene_one_t *scene_one = malloc(sizeof(struct scene_one_t));
  SDL_LogTrace(2, "prepare scene.\n");
  struct scene_t *one = scene_one_prepare(scene_one);
  SDL_LogTrace(2, "switch to scene scene.\n");
  if (!state_switch_scene(s, one)) {
    return SDL_APP_FAILURE;
  }
  return s->app_state;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  struct state_t *s = (struct state_t*)appstate;
  if (s->current_scene == NULL) {
    SDL_LogError(1, "scene is not set.\n");
    return SDL_APP_FAILURE;
  }
  if (!scene_check_events(s->current_scene, event)) {
    SDL_LogError(1, "scene event listener failed.\n");
    return SDL_APP_FAILURE;
  }
  if (!s->current_scene->event(s->current_scene, s, event)) {
    SDL_LogError(1, "scene event failed.\n");
    return SDL_APP_FAILURE;
  }
  return s->app_state;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  struct state_t *s = (struct state_t*)appstate;
  SDL_SetRenderDrawColor(
    s->win.ren,
    s->win.background.r,
    s->win.background.g,
    s->win.background.b,
    s->win.background.a
  );
  SDL_RenderClear(s->win.ren);

  if (s->current_scene == NULL) {
    SDL_LogError(1, "scene is not set.\n");
    return SDL_APP_FAILURE;
  }
  if (!s->current_scene->update(s->current_scene, s)) {
    SDL_LogError(1, "scene update failed.\n");
    return SDL_APP_FAILURE;
  }
  render_array objs = s->current_scene->children;
  for (size_t i = 0; i < objs.len; ++i) {
    struct render_t tmp = objs.render_data[i];
    tmp.render(&tmp.base, s->win.ren);
  }

  SDL_RenderPresent(s->win.ren);
  return s->app_state;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (result == SDL_APP_FAILURE) {
    SDL_LogError(1, "app failed.\n");
  }
  state_free((struct state_t*)appstate);
  TTF_Quit();
}
