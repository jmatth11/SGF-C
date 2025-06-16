#include "loading_icon.h"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "src/logic/base.h"
#include "src/logic/render.h"
#include "src/types/base.h"
#include "src/types/components/loading_icon.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_log.h>
#include "magic.h"
#include "src/logic/render.h"

bool loading_icon_init(struct loading_icon_t *icon, SDL_Renderer *ren, const char *img) {
  SDL_Texture *t = IMG_LoadTexture(ren, img);
  if (t == NULL) {
    SDL_LogError(1, "error loading image: \"%s\"", img);
    return false;
  }
  icon->id = base_id_generate();
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
  if (!render_transparent_fill_rect(ren, icon->background_color, &icon->background)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "error rendering fill rect of icon background");
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
    .id = icon->id,
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
