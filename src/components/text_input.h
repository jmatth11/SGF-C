#ifndef SGF_TEXT_INPUT_H
#define SGF_TEXT_INPUT_H

#include "SDL3/SDL_rect.h"
#include "src/types/base.h"
#include <stdbool.h>

struct text_input_t;
struct font_t;

bool text_input_init(struct text_input_t *ti, struct font_t *font, SDL_FRect rect);
struct render_t text_input_get_render(struct text_input_t *ti);
void text_input_free(struct text_input_t *ti);

#endif
