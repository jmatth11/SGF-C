/**
 * @file color.h
 * @brief Predefined color constants.
 */

#ifndef SGF_COLOR_TYPES_H
#define SGF_COLOR_TYPES_H

#include <SDL3/SDL_pixels.h>

/**
 * @brief White color (255, 255, 255, 255).
 */
#define COLOR_WHITE                                                            \
  (SDL_Color) { 0xFF, 0xFF, 0xFF, 0xFF }
/**
 * @brief Black color (0, 0, 0, 255).
 */
#define COLOR_BLACK                                                            \
  (SDL_Color) { 0x00, 0x00, 0x00, 0xFF }
/**
 * @brief Red color (255, 0, 0, 255).
 */
#define COLOR_RED                                                              \
  (SDL_Color) { 0xFF, 0x00, 0x00, 0xFF }
/**
 * @brief Green color (0, 255, 0, 255).
 */
#define COLOR_GREEN                                                            \
  (SDL_Color) { 0x00, 0xFF, 0x00, 0xFF }
/**
 * @brief Blue color (0, 0, 255, 255).
 */
#define COLOR_BLUE                                                             \
  (SDL_Color) { 0x00, 0x00, 0xFF, 0xFF }
/**
 * @brief Yellow color (255, 255, 0, 255).
 */
#define COLOR_YELLOW                                                           \
  (SDL_Color) { 0xFF, 0xFF, 0x00, 0xFF }

#endif
