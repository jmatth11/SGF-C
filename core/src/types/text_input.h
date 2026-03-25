/**
 * @file text_input.h
 * @brief Text input type definition.
 *
 * TODO: Add char array storage and use TTF_Text only for display.
 */

#ifndef SGF_TEXT_INPUT_TYPE_H
#define SGF_TEXT_INPUT_TYPE_H

#include "SDL3/SDL_rect.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "gap_buffer.h"
#include "../types/base.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct font_t;

/**
 * @brief Interactive text input field.
 */
struct text_input_t {
  /** @brief Unique identifier for this input. */
  base_id id;
  /** @brief Font used for rendering text. */
  struct font_t *font;
  /** @brief SDL_ttf text object for rendering. */
  TTF_Text *text;
  /** @brief Position and size of the input field. */
  SDL_FRect rect;
  /** @brief Gap buffer storing the text content. */
  struct gap_buffer_t str;
  /** @brief Current cursor position (character index). */
  size_t cursor_pos;
  /** @brief Whether the input field currently has focus. */
  bool focused;
};

#endif
