#include "win.h"
#include "src/types/win_types.h"

#include <SDL3/SDL_log.h>

bool win_create_main(struct win_t *win, const char *title, int w, int h) {
  SDL_Window *local_win = NULL;
  SDL_Renderer *local_ren = NULL;
  if (!SDL_CreateWindowAndRenderer(
          title, w, h, SDL_WINDOW_BORDERLESS | SDL_WINDOW_HIGH_PIXEL_DENSITY,
          &local_win, &local_ren)) {
    SDL_Log("error: couldn't create window/renderer -- %s", SDL_GetError());
    return false;
  }
  win->ren = local_ren;
  win->win = local_win;
  return true;
}

void win_free(struct win_t *win) {
  SDL_DestroyRenderer(win->ren);
  SDL_DestroyWindow(win->win);
}
