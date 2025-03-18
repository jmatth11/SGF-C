#ifndef GENERIC_BUTTON_TYPES_H
#define GENERIC_BUTTON_TYPES_H

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdint.h>

#include "src/types/font_types.h"
#include "src/types/theme_types.h"

typedef void(*button_callback)(SDL_MouseButtonEvent *e, void* context);

struct button_t {
  void *context;
  uint32_t id;
  struct theme_t theme;
  /**
   * Properties h and w can be set to -1 to allow automatic sizing based on the label dimensions.
   */
  SDL_FRect rect;
  SDL_Texture* texture;
  button_callback onClick;
  struct label_t label;
  /**
   * Flag to use the x and y properties of rect as center position instead of top left corner.
   */
  bool center;
};

#endif
