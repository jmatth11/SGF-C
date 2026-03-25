/**
 * @file button_types.h
 * @brief Button type definition.
 */

#ifndef GENERIC_BUTTON_TYPES_H
#define GENERIC_BUTTON_TYPES_H

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdint.h>

#include "../types/base.h"
#include "../types/font_types.h"
#include "../types/theme_types.h"

/**
 * @brief Button click callback function type.
 *
 * @param e The mouse button event data.
 * @param context User-provided context pointer.
 */
typedef void (*button_callback)(SDL_MouseButtonEvent *e, void *context);

/**
 * @brief Button UI component.
 */
struct button_t {
  /** @brief User-provided context passed to click callback. */
  void *context;
  /** @brief Unique identifier for this button. */
  base_id id;
  /** @brief Theme colors for the button. */
  struct theme_t theme;
  /** @brief Button rectangle. Set w or h to -1 for auto-sizing based on label. */
  SDL_FRect rect;
  /** @brief Optional texture for button background. */
  SDL_Texture *texture;
  /** @brief Callback function invoked on button click. */
  button_callback onClick;
  /** @brief The text label displayed on the button. */
  struct label_t label;
  /** @brief If true, rect position is treated as center; otherwise top-left corner. */
  bool center;
};

#endif
