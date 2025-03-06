#include "font.h"
#include "SDL3/SDL_log.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <stdbool.h>
#include <stdio.h>

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
    fprintf(stderr, "font was not loaded properly %s\n", SDL_GetError());
    return false;
  }
  // TODO maybe replace and pass in text engine from manager when we switch to
  // that
  f->engine = TTF_CreateRendererTextEngine(ren);
  if (f->engine == NULL) {
    fprintf(stderr, "font was not loaded properly %s\n", SDL_GetError());
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
  l->font = f;
  l->text = NULL;
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

static bool label_render_fn(struct base_t *obj, SDL_Renderer *ren) {
  struct label_t *local = (struct label_t *)obj->parent;
  return label_render(local, ren);
}

struct render_t label_get_render(struct label_t *l) {
  struct base_t base = {
      // TODO add id to label
      .id = 1,
      .parent = l,
  };
  struct render_t result = {
      .base = base,
      .render = label_render_fn,
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
  int x = l->center.x - (width / 2);
  int y = l->center.y - (height / 2);
  return TTF_DrawRendererText(l->text, x, y);
}

bool label_set_center_pos(struct label_t *l, int x, int y) {
  l->center.x = x;
  l->center.y = y;
  return true;
}

SDL_Rect label_get_size(struct label_t *l) {
  SDL_Rect result = {0};
  int width = 0, height = 0;
  if (!TTF_GetTextSize(l->text, &width, &height)) {
    SDL_LogError(1, "getting label text size failed: %s\n", SDL_GetError());
    return result;
  }
  result.x = l->center.x - (width / 2);
  result.y = l->center.y - (height / 2);
  result.w = width;
  result.h = height;
  return result;
}

void label_free(struct label_t *l) {
  if (l == NULL)
    return;
  l->font = NULL;
  if (l->text == NULL)
    return;
  TTF_DestroyText(l->text);
  l->text = NULL;
  unicode_str_destroy(l->str);
  l->str = NULL;
}
