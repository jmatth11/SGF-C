/**
 * @file frame.h
 * @brief Frame component functions.
 */

#ifndef SGF_FRAME_H
#define SGF_FRAME_H

#include "../types/base.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <stdbool.h>

struct frame_t;

/**
 * @brief Initialize a new frame.
 *
 * @param[out] frame Pointer to frame structure to initialize.
 * @return true on success, false on failure.
 */
bool frame_init(struct frame_t *frame);

/**
 * @brief Set the frame size and position.
 *
 * @param[out] frame Pointer to the frame.
 * @param[in] rect Position and size rectangle.
 */
void frame_set_size(struct frame_t *frame, SDL_FRect rect);

/**
 * @brief Get the frame size and position.
 *
 * @param[in] frame Pointer to the frame.
 * @return SDL_FRect containing position and size.
 */
SDL_FRect frame_get_size(struct frame_t *frame);

/**
 * @brief Set the frame fill color.
 *
 * @param[out] frame Pointer to the frame.
 * @param[in] color The fill color.
 */
void frame_set_color(struct frame_t *frame, SDL_Color color);

/**
 * @brief Get the render interface for this frame.
 *
 * @param[in] frame Pointer to the frame.
 * @return render_t structure with render functions.
 */
struct render_t frame_get_render(struct frame_t *frame);

/**
 * @brief Free frame resources.
 *
 * @param[out] frame Pointer to the frame to free.
 */
void frame_free(struct frame_t *frame);

#endif
