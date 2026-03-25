/**
 * @file font.h
 * @brief Font and label component functions.
 */

#ifndef SGF_FONT_H
#define SGF_FONT_H

#include "SDL3/SDL_rect.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>

#include "../types/base.h"
#include "../types/theme_types.h"

struct font_t;
struct label_t;

/**
 * @brief Initialize a font from a file.
 *
 * @param[out] f Pointer to font structure to initialize.
 * @param[in] ren SDL renderer for text engine.
 * @param[in] font_file Path to the font file.
 * @param[in] ptsize Font size in points.
 * @return true on success, false on failure.
 */
bool font_init(struct font_t *f, SDL_Renderer *ren, const char *font_file,
               float ptsize);

/**
 * @brief Free font resources.
 *
 * @param[out] f Pointer to the font to free.
 */
void font_free(struct font_t *f);

/**
 * @brief Initialize a label with a font.
 *
 * @param[out] l Pointer to label structure to initialize.
 * @param[in] f Font to use for the label.
 * @return true on success, false on failure.
 */
bool label_init(struct label_t *l, struct font_t *f);

/**
 * @brief Set the label text content.
 *
 * @param[out] l Pointer to the label.
 * @param[in] text Text string to display.
 * @param[in] length Length of the text string.
 * @return true on success, false on failure.
 */
bool label_set_text(struct label_t *l, const char *text, size_t length);

/**
 * @brief Set label position using center point.
 *
 * @param[out] l Pointer to the label.
 * @param[in] x Center X coordinate.
 * @param[in] y Center Y coordinate.
 * @return true on success, false on failure.
 */
bool label_set_center_pos(struct label_t *l, int x, int y);

/**
 * @brief Set label position using top-left corner.
 *
 * @param[out] l Pointer to the label.
 * @param[in] x Left X coordinate.
 * @param[in] y Top Y coordinate.
 * @return true on success, false on failure.
 */
bool label_set_normal_pos(struct label_t *l, int x, int y);

/**
 * @brief Set text wrapping width.
 *
 * @param[out] l Pointer to the label.
 * @param[in] width Maximum width before wrapping.
 * @return true on success, false on failure.
 */
bool label_set_wrap_length(struct label_t *l, int width);

/**
 * @brief Get the label bounding rectangle.
 *
 * @param[in] l Pointer to the label.
 * @return SDL_Rect containing position and size.
 */
SDL_Rect label_get_size(struct label_t *l);

/**
 * @brief Get the render interface for this label.
 *
 * @param[in] l Pointer to the label.
 * @return render_t structure with render functions.
 */
struct render_t label_get_render(struct label_t *l);

/**
 * @brief Render the label to the screen.
 *
 * @param[in] l Pointer to the label.
 * @param[in] ren SDL renderer (unused, uses internal renderer).
 * @return true on success, false on failure.
 */
bool label_render(struct label_t *l, SDL_Renderer *ren);

/**
 * @brief Free label resources.
 *
 * @param[out] l Pointer to the label to free.
 */
void label_free(struct label_t *l);

#endif
