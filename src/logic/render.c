#include "render.h"
#include "SDL3/SDL_log.h"

bool render_set_blendmode(SDL_Renderer *ren, SDL_BlendMode mode,
                          SDL_BlendMode *old) {
  SDL_BlendMode old_mode = SDL_BLENDMODE_NONE;
  if (!SDL_GetRenderDrawBlendMode(ren, &old_mode)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_RENDER,
                "error getting blend mode from renderer");
    return false;
  }
  if (!SDL_SetRenderDrawBlendMode(ren, mode)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                "error setting blend mode for renderer");
    return false;
  }
  if (old != NULL) {
    *old = old_mode;
  }
  return true;
}

bool render_transparent_fill_rect(SDL_Renderer *ren, SDL_Color color,
                                  SDL_FRect *rect) {
  SDL_BlendMode old_mode = SDL_BLENDMODE_NONE;
  if (!render_set_blendmode(ren, SDL_BLENDMODE_BLEND, &old_mode)) {
    return false;
  }
  if (!SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a)) {
    return false;
  }
  if (!SDL_RenderFillRect(ren, rect)) {
    return false;
  }
  return render_set_blendmode(ren, old_mode, NULL);
}
