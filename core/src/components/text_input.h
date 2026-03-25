/**
 * @file text_input.h
 * @brief Text input component functions.
 */

#ifndef SGF_TEXT_INPUT_H
#define SGF_TEXT_INPUT_H

#include "SDL3/SDL_rect.h"
#include "../types/base.h"
#include <stdbool.h>

struct text_input_t;
struct font_t;

/**
 * @brief Initialize a text input field.
 *
 * @param[out] ti Pointer to text input structure to initialize.
 * @param[in] font Font for rendering text.
 * @param[in] rect Position and size of the input field.
 * @return true on success, false on failure.
 */
bool text_input_init(struct text_input_t *ti, struct font_t *font,
                     SDL_FRect rect);

/**
 * @brief Check if a point is within the input bounds.
 *
 * @param[in] obj Base object wrapper.
 * @param[in] p Point to test.
 * @return true if point is inside input bounds, false otherwise.
 */
bool text_input_point_in_rect(struct base_t *obj, SDL_FPoint p);

/**
 * @brief Handle text input events.
 *
 * @param[in] obj Base object wrapper.
 * @param[in] e SDL event to process.
 * @return true on success, false on failure.
 */
bool text_input_text_event(struct base_t *obj, SDL_Event *e);

/**
 * @brief Get the render interface for this text input.
 *
 * @param[in] ti Pointer to the text input.
 * @return render_t structure with render functions.
 */
struct render_t text_input_get_render(struct text_input_t *ti);

/**
 * @brief Get the event handlers for this text input.
 *
 * @param[in] ti Pointer to the text input.
 * @return events_t structure with event handlers.
 */
struct events_t text_input_get_event(struct text_input_t *ti);

/**
 * @brief Free text input resources.
 *
 * @param[out] ti Pointer to the text input to free.
 */
void text_input_free(struct text_input_t *ti);

#endif
