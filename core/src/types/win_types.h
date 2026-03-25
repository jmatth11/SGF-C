/**
 * @file win_types.h
 * @brief Window type definition.
 */

#ifndef GENERIC_WIN_TYPES_H
#define GENERIC_WIN_TYPES_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

/**
 * @brief Window structure containing SDL window and renderer.
 */
struct win_t {
  /** @brief The SDL window handle. */
  SDL_Window *win;
  /** @brief The SDL renderer for drawing. */
  SDL_Renderer *ren;
  /** @brief Default background color for clearing. */
  SDL_Color background;
};

#endif
