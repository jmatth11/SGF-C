#include "point.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"
#include "src/logic/base.h"
#include "src/logic/render.h"
#include "src/logic/world.h"
#include "src/types/base.h"
#include "src/types/color.h"
#include "src/types/entities/entity.h"
#include "src/types/entities/point.h"
#include "src/types/entities/world_types.h"
#include "src/types/render_interface.h"
#include <SDL3/SDL_log.h>
#include <math.h>
#include <stdlib.h>

#include "src/types/entities/math.h"

/**
 * Initialize point with the given options.
 * If options is NULL, the point is zeroed out.
 */
bool point_init(struct point_t *p, struct point_options_t *options) {
  p->id = base_id_generate();
  p->entity = ZERO_ENTITY;
  p->color = COLOR_BLACK;
  if (options != NULL) {
    p->entity.coord = options->coord;
    p->entity.proj = options->proj;
    p->entity.size = options->size;
    p->color = options->color;
  }
  return true;
}

/**
 * Free point.
 */
void point_free(struct point_t *p) {
  // currently nothing to do.
  (void)p;
}

static bool point_render_fn(struct base_t *obj, struct render_ctx_t *ctx) {
  if (obj == NULL || ctx == NULL || obj->parent == NULL) {
    return false;
  }
  if (ctx->ren == NULL || ctx->world == NULL) {
    return false;
  }
  struct point_t *p = (struct point_t *)obj->parent;
  struct world_t *w = ctx->world;
  SDL_Renderer *ren = ctx->ren;

  SDL_FRect rect = world_apply_to_entity(w, p->entity);
  struct render_attributes_t atts;
  if (!render_get_attributes(ctx->ren, &atts)) {
    return false;
  }
  if (!SDL_SetRenderDrawColor(ren, p->color.r, p->color.g, p->color.b,
                              p->color.a)) {
    return false;
  }
  if (!SDL_RenderFillRect(ren, &rect)) {
    return false;
  }
  return render_set_attributes(ren, &atts);
}

static SDL_FRect point_viewable_rect_fn(struct base_t *obj,
                                        struct viewable_ctx_t *ctx) {
  if (obj == NULL || obj->parent == NULL) {
    return (SDL_FRect){0, 0, 0, 0};
  }
  struct point_t *p = (struct point_t *)obj->parent;
  SDL_FRect result = (SDL_FRect){
      .x = 0,
      .y = 0,
      .w = p->entity.size.w,
      .h = p->entity.size.h,
  };
  if (ctx != NULL && ctx->world != NULL) {
    result = world_apply_to_entity(ctx->world, p->entity);
  }
  return result;
}

/**
 * Get the render vtable of the point.
 */
struct render_t point_get_render(struct point_t *p) {
  struct render_t result;
  result.base = (struct base_t){
      .id = p->id,
      .parent = p,
      .priority = 0,
  };
  result.render = point_render_fn;
  result.get_viewable_rect = point_viewable_rect_fn;
  return result;
}
