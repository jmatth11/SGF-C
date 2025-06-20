#include "win.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL_log.h>

#include "src/types/win_types.h"

bool win_create_main(struct win_t *win, const char *title, int w, int h) {
  SDL_Window *local_win = NULL;
  SDL_Renderer *local_ren = NULL;
  if (!SDL_CreateWindowAndRenderer(
          title, w, h, SDL_WINDOW_HIGH_PIXEL_DENSITY,
          &local_win, &local_ren)) {
    SDL_LogError(1, "error: couldn't create window/renderer -- %s",
                 SDL_GetError());
    return false;
  }
#ifndef __EMSCRIPTEN__
  if (!SDL_SetWindowPosition(local_win, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED)) {
    SDL_LogError(1, "error: couldn't center window -- %s", SDL_GetError());
    return false;
  }
#endif
  if (local_ren == NULL || local_win == NULL) {
    SDL_LogCritical(1, "window or renderer could not be initialised: %s\n",
                    SDL_GetError());
    return false;
  }
  win->ren = local_ren;
  win->win = local_win;
  return true;
}

SDL_Rect win_get_size(struct win_t *win) {
  SDL_Rect result = {
      .x = 0,
      .y = 0,
      .w = 0,
      .h = 0,
  };
  if (!SDL_GetWindowSize(win->win, &result.w, &result.h)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "failed to get window size: %s\n", SDL_GetError());
  }
  return result;
}

void win_free(struct win_t *win) {
  SDL_DestroyRenderer(win->ren);
  SDL_DestroyWindow(win->win);
}
