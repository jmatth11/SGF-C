#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>

#include "src/components/win.h"
#include "src/types/win_types.h"

static struct win_t main_win;
static SDL_FRect rect = {
    .h = 40,
    .w = 90,
    .x = 30,
    .y = 30,
  };

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Simple App", "1.0", "com.example.jmatth11");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

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

  SDL_SetRenderDrawColor(
    main_win.ren,
    main_win.background.r,
    main_win.background.g,
    main_win.background.b,
    main_win.background.a
  );
  SDL_RenderClear(main_win.ren);

  SDL_SetRenderDrawColor(main_win.ren, 0xaa, 0xaa, 0x0, 0xff);
  SDL_RenderFillRect(main_win.ren, &rect);

  SDL_RenderPresent(main_win.ren);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  win_free(&main_win);
}
