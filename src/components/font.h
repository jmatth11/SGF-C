#ifndef SGF_FONT_H
#define SGF_FONT_H

#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>

#include "SDL3/SDL_rect.h"
#include "src/types/theme_types.h"

struct font_t;
struct label_t;

bool font_init(struct font_t *f, SDL_Renderer *ren, const char *font_file, float ptsize);
void font_free(struct font_t *f);

bool label_init(struct label_t *l, struct font_t *f);
bool label_set_text(struct label_t *l, const char *text, size_t length);
bool label_render(struct label_t *l, float x, float y, SDL_Renderer *ren);
void label_free(struct label_t *l);

#endif
