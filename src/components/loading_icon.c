#include "loading_icon.h"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "src/logic/render.h"
#include "src/types/base.h"
#include "src/types/components/loading_icon.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_log.h>
#include "magic.h"

bool loading_icon_init(struct loading_icon_t *icon, SDL_Renderer *ren, const char *img) {
  SDL_Texture *t = IMG_LoadTexture(ren, img);
  if (t == NULL) {
    SDL_LogError(1, "error loading image: \"%s\"", img);
    return false;
  }
  icon->texture = t;
  icon->rotation_speed = 4.0f;
  icon->angle = 0;
  icon->rect = (SDL_FRect){
    0,0,20,20
  };
  icon->background = (SDL_FRect) {0,0,0,0};
  icon->background_color = (SDL_Color){0,0,0,0};
  return true;
}
void loading_icon_update(struct loading_icon_t *icon) {
  icon->angle += icon->rotation_speed;
}
bool loading_icon_render(struct base_t *obj, SDL_Renderer *ren) {
  struct loading_icon_t *icon = (struct loading_icon_t*)obj->parent;
  const SDL_Color b_color = icon->background_color;
  SDL_BlendMode old_mode = SDL_BLENDMODE_NONE;
  if (!render_set_blendmode(ren, SDL_BLENDMODE_BLEND, &old_mode)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "error setting blend mode for loading icon");
  }
  if (!SDL_SetRenderDrawColor(ren, b_color.r, b_color.g, b_color.b, b_color.a)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "error setting render draw color for icon background");
  }
  if (!SDL_RenderFillRect(ren, &icon->background)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "error rendering fill rect of icon background");
  }
  if (!render_set_blendmode(ren, old_mode, NULL)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "error setting blend mode for loading icon");
  }
  SDL_FPoint center = {
    .x = icon->rect.w * 0.5f,
    .y = icon->rect.h * 0.5f,
  };
  SDL_RenderTextureRotated(
    ren,
    icon->texture,
    NULL,
    &icon->rect,
    icon->angle,
    &center,
    false
  );
  return true;
}
struct render_t loading_icon_get_render(struct loading_icon_t *icon) {
  struct base_t b = {
    .id = 1,
    .parent = icon,
  };
  struct render_t ren = {
    .render = loading_icon_render,
    .base = b,
  };
  return ren;
}
void loading_icon_free(struct loading_icon_t *icon) {
  if (icon == NULL) {
    return;
  }
  if (icon->texture != NULL) {
    SDL_DestroyTexture(icon->texture);
  }
}
