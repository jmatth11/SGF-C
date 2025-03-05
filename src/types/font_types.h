#ifndef SGF_FONT_TYPES_H
#define SGF_FONT_TYPES_H

#include <SDL3_ttf/SDL_ttf.h>

#include "array_template.h"

struct font_t {
  TTF_Font *font;
  TTF_TextEngine *engine;
};

generate_array_template(font, struct font_t)

struct font_manager_t {
  // TODO switch to hashmap lookup
  font_array fonts;
  TTF_TextEngine *engine;
};

struct label_t {
  struct font_t *font;
  TTF_Text *text;
  SDL_Point center;
  // TODO maybe add size property
};

#endif
