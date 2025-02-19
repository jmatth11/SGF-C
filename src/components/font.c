#include "font.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "src/types/font_types.h"

bool font_init(struct font_t *f, const char *font_file, float ptsize) {
  if (f == NULL) return false;
  if (font_file == NULL) return false;
  f->font = TTF_OpenFont(font_file, ptsize);
  return f->font != NULL;
}
void font_free(struct font_t *f) {
  if (f == NULL) return;
  if (f->font == NULL) return;
  TTF_CloseFont(f->font);
  f->font = NULL;
}

bool label_init(struct label_t *l, struct font_t *f) {
  if (l == NULL) return false;
  if (f == NULL) return false;
  l->font = f;
  return true;
}

bool label_set_text(struct label_t *l, const char *text, size_t length) {
  if (l == NULL) return false;
  if (text == NULL) return false;
  if (l->text != NULL) {
    TTF_DestroyText(l->text);
  }
  l->text = TTF_CreateText(NULL, l->font->font, text, length);
  return l->text != NULL;
}

void label_free(struct label_t *l) {
  if (l == NULL) return;
  if (l->text == NULL) return;
  TTF_DestroyText(l->text);
  l->text = NULL;
}
