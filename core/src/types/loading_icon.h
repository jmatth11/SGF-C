/**
 * @file loading_icon.h
 * @brief Loading icon type definition.
 */

#ifndef SGF_LOADING_ICON_TYPE_H
#define SGF_LOADING_ICON_TYPE_H

#include "SDL3/SDL_rect.h"
#include "../types/base.h"
#include <SDL3/SDL_render.h>

/**
 * @brief Rotating loading indicator icon.
 */
struct loading_icon_t {
  /** @brief Unique identifier for this icon. */
  base_id id;
  /** @brief Texture to display and rotate. */
  SDL_Texture *texture;
  /** @brief Rotation speed in degrees per update. */
  float rotation_speed;
  /** @brief Current rotation angle. */
  float angle;
  /** @brief Position and size of the icon. */
  SDL_FRect rect;
  /** @brief Background rectangle behind the icon. */
  SDL_FRect background;
  /** @brief Background fill color (supports transparency). */
  SDL_Color background_color;
};

#endif
