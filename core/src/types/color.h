#ifndef SGF_COLOR_TYPES_H
#define SGF_COLOR_TYPES_H

#include <SDL3/SDL_pixels.h>

#define COLOR_WHITE                                                            \
  (SDL_Color) { 0xFF, 0xFF, 0xFF, 0xFF }
#define COLOR_BLACK                                                            \
  (SDL_Color) { 0x00, 0x00, 0x00, 0xFF }
#define COLOR_RED                                                              \
  (SDL_Color) { 0xFF, 0x00, 0x00, 0xFF }
#define COLOR_GREEN                                                            \
  (SDL_Color) { 0x00, 0xFF, 0x00, 0xFF }
#define COLOR_BLUE                                                             \
  (SDL_Color) { 0x00, 0x00, 0xFF, 0xFF }
#define COLOR_YELLOW                                                           \
  (SDL_Color) { 0xFF, 0xFF, 0x00, 0xFF }

#endif
