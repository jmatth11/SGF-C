#include "frame.h"

#include "SDL3/SDL_render.h"
#include "src/logic/base.h"
#include "src/logic/render.h"
#include "src/types/base.h"
#include "src/types/components/frame_types.h"
#include "src/types/render_interface.h"

bool frame_init(struct frame_t *frame) {
  frame->id = base_id_generate();
  frame->rect = (SDL_FRect){0, 0, 0, 0};
  frame->color = (SDL_Color){255, 255, 255, 255};
  return true;
}

void frame_set_size(struct frame_t *frame, SDL_FRect rect) {
  if (frame == NULL) {
    return;
  }
  frame->rect = rect;
}

SDL_FRect frame_get_size(struct frame_t *frame) {
  SDL_FRect result = {0, 0, 0, 0};
  if (frame != NULL) {
    result = frame->rect;
  }
  return result;
}

void frame_set_color(struct frame_t *frame, SDL_Color color) {
  if (frame == NULL) {
    return;
  }
  frame->color = color;
}

static SDL_FRect frame_get_view_size(struct base_t *b,
                                     struct viewable_ctx_t *ctx) {
  (void)ctx;
  if (b == NULL) {
    return (SDL_FRect){0, 0, 0, 0};
  }
  struct frame_t *local = (struct frame_t *)b->parent;
  return local->rect;
}

static bool frame_render(struct base_t *obj, struct render_ctx_t *ctx) {
  if (!render_check_args(obj, ctx)) {
    return false;
  }
  SDL_Renderer *ren = ctx->ren;
  struct render_attributes_t atts;
  if (!render_get_attributes(ren, &atts)) {
    return false;
  }
  struct frame_t *local = (struct frame_t *)obj->parent;
  if (local == NULL) {
    return false;
  }
  if (!SDL_SetRenderDrawColor(ren, local->color.r, local->color.g,
                              local->color.b, local->color.a)) {
    return false;
  }
  if (!SDL_RenderFillRect(ren, &local->rect)) {
    return false;
  }
  return render_set_attributes(ren, &atts);
}

struct render_t frame_get_render(struct frame_t *frame) {
  struct render_t result = {0};
  if (frame == NULL) {
    return result;
  }
  result.base = (struct base_t){
      .id = frame->id,
      .parent = frame,
      .priority = 0,
  };
  result.get_viewable_rect = frame_get_view_size;
  result.render = frame_render;
  return result;
}

void frame_free(struct frame_t *frame) {
  if (frame == NULL) {
    return;
  }
}
