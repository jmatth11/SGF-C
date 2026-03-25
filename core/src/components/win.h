/**
 * @file win.h
 * @brief Window management functions.
 */

#ifndef GENERIC_WIN_H
#define GENERIC_WIN_H

#include <SDL3/SDL_rect.h>
#include <stdbool.h>

// forward declare
struct win_t;

/**
 * @brief Create the main application window and renderer.
 *
 * @param[out] win Pointer to win_t to populate.
 * @param[in] title Window title.
 * @param[in] w Window width in pixels.
 * @param[in] h Window height in pixels.
 * @return true on success, false on failure.
 */
bool win_create_main(struct win_t *win, const char *title, int w, int h);

/**
 * @brief Get the current window size.
 *
 * @param win Pointer to the window structure.
 * @return SDL_Rect containing width and height.
 */
SDL_Rect win_get_size(struct win_t *win);

/**
 * @brief Free window and renderer resources.
 *
 * @param win Pointer to the window structure to free.
 */
void win_free(struct win_t *win);

#endif
