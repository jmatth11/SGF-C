#ifndef SGF_FRAME_H
#define SGF_FRAME_H

#include "src/types/base.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdbool.h>

struct frame_t;

/**
 * Initialize.
 */
bool frame_init(struct frame_t *frame);

/**
 * Set the size of the frame.
 */
void frame_set_size(struct frame_t *frame, SDL_FRect rect);

/**
 * Get the size of the frame.
 */
SDL_FRect frame_get_size(struct frame_t *frame);

/**
 * Set the color of the frame.
 */
void frame_set_color(struct frame_t *frame, SDL_Color color);

/**
 * Get the renderer of the frame.
 */
struct render_t frame_get_render(struct frame_t *frame);

/**
 * Free frame internals.
 */
void frame_free(struct frame_t *frame);

#endif
