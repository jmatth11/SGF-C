/**
 * @file toast.h
 * @brief Toast notification component functions.
 */

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
 * @brief Create a new toast notification.
 *
 * @param[in] font Font for the toast message.
 * @param[in] text Text to display.
 * @param[in] length Length of the text.
 * @param[in] _type Toast type (TOAST_SUCCESS, TOAST_WARN, TOAST_ERROR).
 * @param[in] _placement Screen placement (enum toast_placement_t).
 * @param[in] window_size Window bounds for placement. NULL for safe area.
 * @return Newly allocated toast, or NULL on failure.
 */
struct toast_t *toast_create(struct font_t *font, const char *text,
                             size_t length, int _type, int _placement,
                             SDL_FRect *window_size) __nonnull((1, 2));

/**
 * @brief Set the toast message text.
 *
 * @param[out] t Toast to modify.
 * @param[in] text New message text.
 * @param[in] length Length of the text.
 * @return true on success, false on failure.
 */
bool toast_set_message(struct toast_t *t, const char *text, size_t length)
    __nonnull((1, 2));

/**
 * @brief Set the toast type.
 *
 * @param[out] t Toast to modify.
 * @param[in] _type New toast type.
 * @return true on success, false on failure.
 */
bool toast_set_type(struct toast_t *t, int _type) __nonnull((1));

/**
 * @brief Set the toast placement position.
 *
 * @param[out] t Toast to modify.
 * @param[in] _placement New placement position.
 * @param[in] window_size Window bounds for placement. NULL for safe area.
 * @return true on success, false on failure.
 */
bool toast_set_placement(struct toast_t *t, int _placement,
                         SDL_FRect *window_size) __nonnull((1));

/**
 * @brief Get render interface for a toast.
 *
 * @param[in] t Toast to render.
 * @return render_t structure with render functions.
 */
struct render_t toast_prepare_render(struct toast_t *t) __nonnull((1));

/**
 * @brief Destroy a toast.
 *
 * @param[out] t Pointer to toast pointer to free.
 */
void toast_destroy(struct toast_t **t);

/**
 * @brief Create a toast manager for queueing notifications.
 *
 * @return Newly allocated toast manager, or NULL on failure.
 */
struct toast_manager_t *toast_manager_create();

/**
 * @brief Add a toast to the queue.
 *
 * @param[out] tm Toast manager.
 * @param[in] toast Toast to queue.
 * @return true on success, false on failure.
 */
bool toast_manager_push(struct toast_manager_t *tm, struct toast_t *toast)
    __nonnull((1, 2));

/**
 * @brief Update toast manager and display next toast if ready.
 *
 * @param[out] tm Toast manager.
 * @param[in] scene Scene to add toast to.
 * @return true on success, false on failure.
 */
bool toast_manager_update(struct toast_manager_t *tm, struct scene_t *scene)
    __nonnull((1));

/**
 * @brief Destroy toast manager and all queued toasts.
 *
 * @param[out] tm Pointer to toast manager pointer to free.
 */
void toast_manager_destroy(struct toast_manager_t **tm);

#endif
