#include "render.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "src/types/base.h"
#include "src/types/render_interface.h"

bool render_check_args(struct base_t *obj, struct render_ctx_t *ctx) {
  return (obj != NULL && ctx != NULL && obj->parent != NULL &&
          ctx->ren != NULL);
}

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

bool render_get_attributes(SDL_Renderer *ren, struct render_attributes_t *out) {
  if (ren == NULL) {
    return false;
  }
  if (out == NULL) {
    return false;
  }
  SDL_BlendMode old_mode = SDL_BLENDMODE_NONE;
  if (!SDL_GetRenderDrawBlendMode(ren, &old_mode)) {
    return false;
  }
  out->blend_mode = old_mode;
  SDL_Color old_color = (SDL_Color){0, 0, 0, 0};
  if (!SDL_GetRenderDrawColor(ren, &old_color.r, &old_color.g, &old_color.b,
                              &old_color.a)) {
    return false;
  }
  out->color = old_color;
  return true;
}

bool render_set_attributes(SDL_Renderer *ren, struct render_attributes_t *att) {
  if (ren == NULL) {
    return false;
  }
  if (att == NULL) {
    return false;
  }
  if (!SDL_SetRenderDrawBlendMode(ren, att->blend_mode)) {
    return false;
  }
  if (!SDL_SetRenderDrawColor(ren, att->color.r, att->color.g, att->color.b,
                              att->color.a)) {
    return false;
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
