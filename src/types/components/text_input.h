#ifndef SGF_TEXT_INPUT_TYPE_H
#define SGF_TEXT_INPUT_TYPE_H

#include "SDL3/SDL_rect.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "gap_buffer.h"
#include "src/types/base.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct font_t;

struct text_input_t {
  // TODO add char array in here to keep track of text
  // only use TTF_Text as display.
  base_id id;
  struct font_t *font;
  TTF_Text *text;
  SDL_FRect rect;
  struct gap_buffer_t str;
  size_t cursor_pos;
  bool focused;
};

#endif
