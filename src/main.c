#include <stdio.h>
#include "SDL3/SDL_init.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "src/scenes/start.h"
#include "src/types/scene_types.h"
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include "src/components/button.h"
#include "src/logic/state.h"
#include "src/types/components/button_types.h"
#include "src/types/state.h"
#include <SDL3/SDL_log.h>

#include "src/components/win.h"
#include "src/types/win_types.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Simple App", "1.0", "com.example.jmatth11");
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  if (!TTF_Init()) {
    SDL_Log("Couldn't initialize SDL_TTF: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  struct state_t *s = malloc(sizeof(struct state_t));
  if (!state_init(s)) {
    SDL_Log("state failed to initialize");
    return SDL_APP_FAILURE;
  }
  *appstate = s;
  struct scene_one_t *scene_one = malloc(sizeof(struct scene_one_t));
  struct scene_t *one = scene_one_prepare(scene_one);
  if (!state_switch_scene(s, one)) {
    return SDL_APP_FAILURE;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  struct state_t *s = (struct state_t*)appstate;
  if (s->current_scene == NULL) {
    fprintf(stderr, "scene is not set.\n");
    return SDL_APP_FAILURE;
  }
  if (!s->current_scene->event(s->current_scene, s, event)) {
    fprintf(stderr, "scene event failed.\n");
    return SDL_APP_FAILURE;
  }
  return SDL_APP_CONTINUE;
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
    fprintf(stderr, "scene is not set.\n");
    return SDL_APP_FAILURE;
  }
  if (!s->current_scene->update(s->current_scene, s)) {
    fprintf(stderr, "scene update failed.\n");
    return SDL_APP_FAILURE;
  }
  render_array objs = s->current_scene->children;
  for (size_t i = 0; i < objs.len; ++i) {
    struct render_t tmp = objs.render_data[i];
    tmp.render(&tmp.base, s->win.ren);
  }

  SDL_RenderPresent(s->win.ren);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (result == SDL_APP_FAILURE) {
    fprintf(stderr, "app failed.\n");
  }
  state_free((struct state_t*)appstate);
  TTF_Quit();
}
