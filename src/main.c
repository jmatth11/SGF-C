#include "SDL3/SDL_init.h"
#include "SDL3_ttf/SDL_ttf.h"
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

  main_win.background = (SDL_Color){
    .r = 0x0,
    .g = 0x0,
    .b = 0x0,
    .a = 0xff
  };

  if (!win_create_main(&main_win, "Simple Example", 640, 480)) {
    return SDL_APP_FAILURE;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  switch (event->button.type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        SDL_Log("event mouse button");
        SDL_FPoint p = { .x = event->button.x, .y = event->button.y };
        SDL_Log("x=%f, y=%f", p.x, p.y);
        if (SDL_PointInRectFloat(&p, &rect)) {
          SDL_Log("point is in rect");
        }
      break;
    }
    default:
      break;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  struct state_t *s = (struct state_t*)appstate;
  SDL_SetRenderDrawColor(
    main_win.ren,
    main_win.background.r,
    main_win.background.g,
    main_win.background.b,
    main_win.background.a
  );
  SDL_RenderClear(main_win.ren);

  render_array objs = s->objects;
  for (size_t i = 0; i < objs.len; ++i) {
    struct render_interface tmp = objs.render_data[i];
    tmp.render(main_win.ren, tmp.context);
  }

  SDL_RenderPresent(main_win.ren);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  win_free(&main_win);
  state_free((struct state_t*)appstate);
  TTF_Quit();
}
