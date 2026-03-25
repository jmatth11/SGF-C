/**
 * @file font_types.h
 * @brief Font and label type definitions.
 *
 * TODO: Switch font_manager_t to use hashmap lookup for better performance.
 * TODO: Add size property to label_t for explicit dimensions.
 */

#ifndef SGF_FONT_TYPES_H
#define SGF_FONT_TYPES_H

#include <SDL3_ttf/SDL_ttf.h>

#include "array_template.h"
#include "../types/base.h"
#include "unicode_str.h"

/**
 * @brief Font wrapper for SDL_ttf.
 */
struct font_t {
  /** @brief The SDL_ttf font handle. */
  TTF_Font *font;
  /** @brief The text engine for rendering. */
  TTF_TextEngine *engine;
};

/**
 * @brief Dynamic array of fonts.
 */
generate_array_template(font, struct font_t)

/**
 * @brief Font manager for handling multiple fonts.
 */
    struct font_manager_t {
  /** @brief Array of loaded fonts. */
  font_array fonts;
  /** @brief The text engine used by all fonts. */
  TTF_TextEngine *engine;
};

/**
 * @brief Text label for displaying text on screen.
 */
struct label_t {
  /** @brief Unique identifier for this label. */
  base_id id;
  /** @brief The font used for rendering. */
  struct font_t *font;
  /** @brief The SDL_ttf text object. */
  TTF_Text *text;
  /** @brief Internal string buffer for text data. */
  struct unicode_str_t *str;
  /** @brief Screen position of the label. */
  SDL_Point position;
  /** @brief If true, position is the center; otherwise top-left corner. */
  bool is_centered;
};

#endif
