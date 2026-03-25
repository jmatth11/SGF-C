/**
 * @file theme_types.h
 * @brief Theme type definition.
 *
 * TODO: Add font/TTF support to theme structure.
 */

#ifndef SGF_THEME_TYPES_H
#define SGF_THEME_TYPES_H

#include <SDL3/SDL_pixels.h>

/**
 * @brief Theme structure for UI component styling.
 */
struct theme_t {
  /** @brief Primary color for the theme. */
  SDL_Color color;
};

#endif
