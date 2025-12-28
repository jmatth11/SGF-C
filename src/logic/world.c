#include "world.h"
#include "src/components/win.h"
#include "src/entities/entity.h"
#include "src/logic/geometry.h"
#include "src/types/entities/entity.h"
#include "src/types/entities/world_types.h"

#include <SDL3/SDL_log.h>

static SDL_FPoint project(const struct world_t *w, float x, float y, float z) {
  if (z == 0 || w == NULL) {
    return (SDL_FPoint){
        .x = 0,
        .y = 0,
    };
  }
  const double scale = w->focal_length / z;
  return (SDL_FPoint){
      .x = x * scale,
      .y = y * scale,
  };
}

static SDL_FPoint to_screen(const struct world_t *w,
                            struct coordinate_t coord) {
  return (SDL_FPoint){
      .x = ((coord.x + 1.0) / 2.0) * w->rect.w,
      .y = (1 - ((coord.y + 1.0) / 2.0)) * w->rect.h,
  };
}

bool world_init_with_rect(struct world_t *w, SDL_FRect rect) {
  w->rect = rect;
  w->scale = 1.0f;
  w->focal_length = 1.0f;
  w->close_cutoff = 0.001f;
  w->far_cutoff = 25.0f;
  return true;
}

bool world_init_with_win(struct world_t *w, struct win_t *win) {
  SDL_Rect rect = win_get_size(win);
  w->rect = (SDL_FRect){
      .x = 0,
      .y = 0,
      .w = rect.w,
      .h = rect.h,
  };
  w->scale = 1.0f;
  w->focal_length = 1.0f;
  w->close_cutoff = 0.001f;
  w->far_cutoff = 25.0f;
  return true;
}

SDL_FRect world_apply(const struct world_t *w, SDL_FRect rect) {
  SDL_FRect result = rect;
  result.x += (w->rect.x * w->scale);
  result.y += (w->rect.y * w->scale);
  result.w *= w->scale;
  result.h *= w->scale;
  return result;
}

SDL_FRect world_apply_to_entity(const struct world_t *w, struct entity_t ent) {
  if (ent.proj.z <= w->close_cutoff || ent.proj.z >= w->far_cutoff) {
    return (SDL_FRect){0, 0, 0, 0};
  }
  const SDL_FPoint proj_point =
      project(w, ent.coord.x + ent.proj.x, ent.coord.y + ent.proj.y,
              ent.coord.z + ent.proj.z);
  const SDL_FPoint screen_point = to_screen(w, (struct coordinate_t){
                                                   .x = proj_point.x,
                                                   .y = proj_point.y,
                                               });

  struct area_t size = ent.size;
  if (ent.adjust_size) {
    size = (struct area_t){
        .w = ent.size.w * (1 / ent.proj.z),
        .h = ent.size.h * (1 / ent.proj.z),
    };
  }
  return world_apply(w, (SDL_FRect){
                            .x = (screen_point.x - (size.w / 2.0)),
                            .y = (screen_point.y - (size.h / 2.0)),
                            .w = size.w,
                            .h = size.h,
                        });
}

bool world_should_draw(const struct world_t *w, const SDL_Rect *render_rect,
                       const SDL_FRect *rect) {
  if (w == NULL || render_rect == NULL || rect == NULL) {
    return false;
  }
  if (rect->w == 0 || rect->h == 0) {
    return false;
  }
  const SDL_FRect offset_rect = world_apply(w, *rect);
  return rectWithinRect(offset_rect, (*render_rect));
}

bool world_should_draw_ent(const struct world_t *w, const SDL_Rect *render_rect,
                           const struct entity_t *ent) {
  if (w == NULL || render_rect == NULL || ent == NULL) {
    return false;
  }
  const SDL_FRect offset_rect = world_apply_to_entity(w, *ent);
  if (offset_rect.w == 0 || offset_rect.h == 0) {
    return false;
  }
  return rectWithinRect(offset_rect, (*render_rect));
}
