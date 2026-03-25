/**
 * @file render_interface.h
 * @brief Render attributes type definition.
 */

#ifndef GENERIC_RENDER_INTERFACE_TYPE_H
#define GENERIC_RENDER_INTERFACE_TYPE_H

#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_pixels.h"
#include <SDL3/SDL_render.h>

/**
 * @brief Render state attributes for save/restore operations.
 */
struct render_attributes_t {
  /** @brief Current draw color. */
  SDL_Color color;
  /** @brief Current blend mode. */
  SDL_BlendMode blend_mode;
};

#endif
