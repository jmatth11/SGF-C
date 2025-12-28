#include "font.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "src/logic/base.h"
#include <stdbool.h>
#include <stdio.h>

#include "src/logic/render.h"
#include "src/types/base.h"
#include "src/types/font_types.h"
#include "unicode_str.h"

bool font_init(struct font_t *f, SDL_Renderer *ren, const char *font_file,
               float ptsize) {
  if (f == NULL)
    return false;
  if (font_file == NULL)
    return false;
  f->engine = NULL;
  f->font = TTF_OpenFont(font_file, ptsize);
  if (f->font == NULL) {
    SDL_LogError(1, "font was not loaded properly %s\n", SDL_GetError());
    return false;
  }
  // TODO maybe replace and pass in text engine from manager when we switch to
  // that
  f->engine = TTF_CreateRendererTextEngine(ren);
  if (f->engine == NULL) {
    SDL_LogError(1, "font was not loaded properly %s\n", SDL_GetError());
    return false;
  }
  return f->font != NULL;
}
void font_free(struct font_t *f) {
  if (f == NULL)
    return;
  if (f->font == NULL)
    return;
  TTF_CloseFont(f->font);
  // TODO pull out once we are using the font_manager_t
  if (f->engine != NULL) {
    TTF_DestroyRendererTextEngine(f->engine);
  }
  f->font = NULL;
}

bool label_init(struct label_t *l, struct font_t *f) {
  if (l == NULL)
    return false;
  if (f == NULL)
    return false;
  l->id = base_id_generate();
  l->font = f;
  l->text = NULL;
  l->is_centered = false;
  l->str = unicode_str_create();
  if (l->str == NULL) {
    return false;
  }
  return true;
}

bool label_set_text(struct label_t *l, const char *text, size_t length) {
  if (l == NULL)
    return false;
  if (l->font == NULL)
    return false;
  if (text == NULL)
    return false;
  if (l->str == NULL)
    return false;
  const size_t n = unicode_str_set_char(l->str, text, length);
  if (length != 0 && n == 0)
    return false;
  if (l->text == NULL) {
    l->text = TTF_CreateText(l->font->engine, l->font->font, text, length);
  } else {
    if (!TTF_SetTextString(l->text, text, length)) {
      SDL_LogError(1, "failed to set text on label: %s\n", SDL_GetError());
      return false;
    }
  }
  return l->text != NULL;
}

static bool label_render_fn(struct base_t *obj, struct render_ctx_t *ctx) {
  if (!render_check_args(obj, ctx)) {
    return false;
  }
  struct label_t *local = (struct label_t *)obj->parent;
  return label_render(local, ctx->ren);
}

static SDL_FRect label_get_viewable_size(struct base_t *b,
                                         struct viewable_ctx_t *ctx) {
  (void)ctx;
  struct label_t *local = (struct label_t *)b->parent;
  SDL_Rect rect = label_get_size(local);
  return (SDL_FRect){
      .x = rect.x,
      .y = rect.y,
      .w = rect.w,
      .h = rect.h,
  };
}

struct render_t label_get_render(struct label_t *l) {
  struct base_t base = {
      .id = l->id,
      .parent = l,
      .priority = 0,
  };
  struct render_t result = {
      .base = base,
      .render = label_render_fn,
      .get_viewable_rect = label_get_viewable_size,
  };
  return result;
}

bool label_render(struct label_t *l, SDL_Renderer *ren) {
  (void)ren;
  // TODO put condition where you can pass in a renderer to use a different one
  // if desired.
  int width = 0, height = 0;
  if (!TTF_GetTextSize(l->text, &width, &height)) {
    SDL_LogError(1, "getting label text size failed: %s\n", SDL_GetError());
    return false;
  }
  int x = l->position.x;
  int y = l->position.y;
  if (l->is_centered) {
    x = l->position.x - (width / 2);
    y = l->position.y - (height / 2);
  }
  return TTF_DrawRendererText(l->text, x, y);
}

bool label_set_center_pos(struct label_t *l, int x, int y) {
  l->is_centered = true;
  l->position.x = x;
  l->position.y = y;
  return true;
}

bool label_set_normal_pos(struct label_t *l, int x, int y) {
  l->is_centered = false;
  l->position.x = x;
  l->position.y = y;
  return true;
}

bool label_set_wrap_length(struct label_t *l, int width) {
  return TTF_SetTextWrapWidth(l->text, width);
}

SDL_Rect label_get_size(struct label_t *l) {
  SDL_Rect result = {0};
  int width = 0, height = 0;
  if (!TTF_GetTextSize(l->text, &width, &height)) {
    SDL_LogError(1, "getting label text size failed: %s\n", SDL_GetError());
    return result;
  }
  if (l->is_centered) {
    result.x = l->position.x - (width / 2);
    result.y = l->position.y - (height / 2);
  } else {
    result.x = l->position.x;
    result.y = l->position.y;
  }
  result.w = width;
  result.h = height;
  return result;
}

void label_free(struct label_t *l) {
  if (l == NULL) {
    return;
  }
  l->font = NULL;
  if (l->text == NULL) {
    return;
  }
  TTF_DestroyText(l->text);
  l->text = NULL;
  unicode_str_destroy(&l->str);
  l->str = NULL;
}
