#ifndef SGF_FONT_H
#define SGF_FONT_H

#include "SDL3/SDL_rect.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>

#include "src/types/base.h"
#include "src/types/theme_types.h"

struct font_t;
struct label_t;

bool font_init(struct font_t *f, SDL_Renderer *ren, const char *font_file,
               float ptsize);
void font_free(struct font_t *f);

bool label_init(struct label_t *l, struct font_t *f);
bool label_set_text(struct label_t *l, const char *text, size_t length);
bool label_set_center_pos(struct label_t *l, int x, int y);
bool label_set_normal_pos(struct label_t *l, int x, int y);
bool label_set_wrap_length(struct label_t *l, int width);
SDL_Rect label_get_size(struct label_t *l);
struct render_t label_get_render(struct label_t *l);
bool label_render(struct label_t *l, SDL_Renderer *ren);
void label_free(struct label_t *l);

#endif
