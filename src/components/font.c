#include "font.h"
#include <stdbool.h>
#include <stdio.h>
#include "SDL3_ttf/SDL_ttf.h"

#include "src/types/font_types.h"

bool font_init(struct font_t *f, SDL_Renderer *ren, const char *font_file, float ptsize) {
  if (f == NULL) return false;
  if (font_file == NULL) return false;
  f->engine = NULL;
  f->font = TTF_OpenFont(font_file, ptsize);
  if (f->font == NULL) {
    fprintf(stderr, "font was not loaded properly %s\n", SDL_GetError());
    return false;
  }
  // TODO maybe replace and pass in text engine from manager when we switch to that
  f->engine = TTF_CreateRendererTextEngine(ren);
  if (f->engine == NULL) {
    fprintf(stderr, "font was not loaded properly %s\n", SDL_GetError());
    return false;
  }
  return f->font != NULL;
}
void font_free(struct font_t *f) {
  if (f == NULL) return;
  if (f->font == NULL) return;
  TTF_CloseFont(f->font);
  // TODO pull out once we are using the font_manager_t
  if (f->engine != NULL) {
    TTF_DestroyRendererTextEngine(f->engine);
  }
  f->font = NULL;
}

bool label_init(struct label_t *l, struct font_t *f) {
  if (l == NULL) return false;
  if (f == NULL) return false;
  l->font = f;
  l->text = NULL;
  return true;
}

bool label_set_text(struct label_t *l, const char *text, size_t length) {
  if (l == NULL) return false;
  if (l->font == NULL) return false;
  if (text == NULL) return false;
  if (l->text != NULL) {
    TTF_DestroyText(l->text);
  }
  l->text = TTF_CreateText(l->font->engine, l->font->font, text, length);
  return l->text != NULL;
}

bool label_render(struct label_t *l, float x, float y, SDL_Renderer *ren) {
  // TODO put condition where you can pass in a renderer to use a different one if desired.
  return TTF_DrawRendererText(l->text, x, y);
}

void label_free(struct label_t *l) {
  if (l == NULL) return;
  l->font = NULL;
  if (l->text == NULL) return;
  TTF_DestroyText(l->text);
  l->text = NULL;
}
