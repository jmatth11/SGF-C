#include "world.h"
#include "src/components/win.h"
#include "src/entities/entity.h"
#include "src/types/entities/entity.h"
#include "src/types/entities/world_types.h"

#include <SDL3/SDL_log.h>

static SDL_FPoint project(float x, float y, float z) {
  if (z == 0) {
    return (SDL_FPoint){
        .x = 0,
        .y = 0,
    };
  }
  const double scale = 1.0 / z;
  return (SDL_FPoint){
      .x = x * scale,
      .y = y * scale,
  };
}

static SDL_FPoint to_screen(struct world_t *w, struct coordinate_t coord) {
  return (SDL_FPoint){
      .x = ((coord.x + 1.0) / 2.0) * w->rect.w,
      .y = (1 - ((coord.y + 1.0) / 2.0)) * w->rect.h,
  };
}

bool world_init_with_rect(struct world_t *w, SDL_FRect rect) {
  w->rect = rect;
  w->scale = 1.0f;
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
  return true;
}

SDL_FRect world_apply(struct world_t *w, SDL_FRect rect) {
  SDL_FRect result = rect;
  result.x += (w->rect.x * w->scale);
  result.y += (w->rect.y * w->scale);
  result.w *= w->scale;
  result.h *= w->scale;
  return result;
}

SDL_FRect world_apply_to_entity(struct world_t *w, struct entity_t ent) {
  if (ent.proj_z == 0) {
    return (SDL_FRect){0, 0, 0, 0};
  }
  const SDL_FPoint proj_point =
      project(ent.coord.x, ent.coord.y, ent.coord.z + ent.proj_z);
  const SDL_FPoint screen_point = to_screen(w, (struct coordinate_t){
                                                   .x = proj_point.x,
                                                   .y = proj_point.y,
                                               });
  return world_apply(w, (SDL_FRect){
                            .x = (screen_point.x - (ent.size.w / 2.0)),
                            .y = (screen_point.y - (ent.size.h / 2.0)),
                            .w = ent.size.w,
                            .h = ent.size.h,
                        });
}
