#ifndef SGF_FONT_TYPES_H
#define SGF_FONT_TYPES_H

#include "deps/array_template/array_template.h"
#include <SDL3_ttf/SDL_ttf.h>

struct font_t {
  TTF_Font *font;
};

generate_array_template(font, struct font_t)

struct font_manager_t {
  // TODO switch to hashmap lookup
  font_array fonts;
};

struct label_t {
  struct font_t *font;
  TTF_Text *text;
  // TODO maybe add size property
};

#endif
