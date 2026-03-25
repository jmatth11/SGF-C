/**
 * @file button.h
 * @brief Button component functions.
 */

#ifndef GENERIC_BUTTON_H
#define GENERIC_BUTTON_H

#include "../types/base.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct button_t;
struct font_t;

/**
 * @brief Initialize a new button.
 *
 * @param[out] button Pointer to button structure to initialize.
 * @param[in] font Font to use for the button label.
 * @return true on success, false on failure.
 */
bool button_init(struct button_t *button, struct font_t *font);

/**
 * @brief Get the render interface for this button.
 *
 * @param[in] button Pointer to the button.
 * @return render_t structure with render functions.
 */
struct render_t button_get_render(struct button_t *button);

/**
 * @brief Set the button text.
 *
 * @param[out] button Pointer to the button.
 * @param[in] str Text string to display.
 * @param[in] len Length of the text string.
 * @return true on success, false on failure.
 */
bool button_set_text(struct button_t *button, const char *str, size_t len);

/**
 * @brief Get the button rectangle.
 *
 * @param[in] button Pointer to the button.
 * @return SDL_FRect containing position and size.
 */
SDL_FRect button_get_rect(struct button_t *button);

/**
 * @brief Free button resources.
 *
 * @param[out] button Pointer to the button to free.
 */
void button_free(struct button_t *button);

#endif
