#ifndef SGF_TOAST_H
#define SGF_TOAST_H

#include "SDL3/SDL_rect.h"
#include "defs.h"
#include <stdbool.h>
#include <stddef.h>

struct toast_t;
struct font_t;
struct render_t;
struct toast_manager_t;
struct scene_t;

/**
 * Create a toast structure with the given data.
 *
 * @param font The font to use.
 * @param text The text to display.
 * @param length The length of the text.
 * @param _type The toast type. See enum toast_type_t. Invalid types default to
 * error type.
 * @param _placement The default placement. See enum toast_placement_t. Invalid
 * placements will default to bottom right.
 * @param window_size The rect size of the window to be placed on.
 * If NULL the renderer safe area size will be used.
 * @return True on success, false otherwise.
 */
struct toast_t *toast_create(struct font_t *font, const char *text,
                             size_t length, int _type, int _placement,
                             SDL_FRect *window_size) __nonnull((1, 2));

/**
 * Set the message of the toast structure.
 *
 * @param t The toast structure.
 * @param text The message.
 * @param length The length of the message.
 * @return True on success, false otherwise.
 */
bool toast_set_message(struct toast_t *t, const char *text, size_t length)
    __nonnull((1, 2));
/**
 * Set the toast's type.
 *
 * @param t The toast structure.
 * @param _type The type. See enum toast_type_t.
 * @return True on success, false otherwise.
 */
bool toast_set_type(struct toast_t *t, int _type) __nonnull((1));

/**
 * Set the placement of the toast.
 *
 * @param t The toast structure.
 * @param _placement The default placement. See enum toast_placement_t. Invalid
 * placements will default to bottom right.
 * @param window_size The rect size of the window to be placed on.
 * If NULL the renderer safe area size will be used.
 * @return True on success, false otherwise.
 */
bool toast_set_placement(struct toast_t *t, int _placement,
                         SDL_FRect *window_size) __nonnull((1));

struct render_t toast_prepare_render(struct toast_t *t) __nonnull((1));

void toast_destroy(struct toast_t **t);

/* Toast Manager */

struct toast_manager_t *toast_manager_create();
bool toast_manager_push(struct toast_manager_t *tm, struct toast_t *toast)
    __nonnull((1, 2));
bool toast_manager_update(struct toast_manager_t *tm, struct scene_t *scene)
    __nonnull((1));
void toast_manager_destroy(struct toast_manager_t **tm);

#endif
