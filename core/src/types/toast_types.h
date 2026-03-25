/**
 * @file toast_types.h
 * @brief Toast notification type definitions.
 */

#ifndef SGF_TOAST_TYPES_H
#define SGF_TOAST_TYPES_H

#include "queue.h"
#include "../types/base.h"
#include "../types/font_types.h"
#include <stdbool.h>

/**
 * @brief Toast notification types.
 */
enum toast_type_t {
  /** @brief Success notification (green). */
  TOAST_SUCCESS = 0,
  /** @brief Warning notification (yellow). */
  TOAST_WARN,
  /** @brief Error notification (red). */
  TOAST_ERROR,
};

/**
 * @brief Toast screen placement positions.
 */
enum toast_placement_t {
  /** @brief Top-right corner. */
  TOAST_TOP_RIGHT,
  /** @brief Top-left corner. */
  TOAST_TOP_LEFT,
  /** @brief Top center. */
  TOAST_TOP_CENTER,
  /** @brief Bottom-left corner. */
  TOAST_BOTTOM_LEFT,
  /** @brief Bottom center. */
  TOAST_BOTTOM_CENTER,
  /** @brief Bottom-right corner. */
  TOAST_BOTTOM_RIGHT,
};

/**
 * @brief Toast notification structure.
 */
struct toast_t {
  /** @brief Unique identifier for this toast. */
  base_id id;
  /** @brief Type of toast (success, warn, error). */
  enum toast_type_t type;
  /** @brief Screen placement position. */
  enum toast_placement_t placement;
  /** @brief Text label for the toast message. */
  struct label_t msg;
  /** @brief Size of the toast. Use 0 values for auto-sizing. */
  SDL_FRect rect;
  /** @brief Screen bounds for placement calculation. */
  SDL_FRect placement_rect;
};

/**
 * @brief Toast manager for queueing and displaying notifications.
 */
struct toast_manager_t {
  /** @brief Queue of pending toasts. */
  struct simple_queue_t *toasts;
  /** @brief Currently displayed toast, or NULL if none. */
  struct toast_t *current_toast;
  /** @brief Scene the toast manager is attached to. */
  struct scene_t *parent_scene;
  /** @brief Font used for toast messages. */
  struct font_t *font;
  /** @brief Whether ready to display next toast. */
  bool display_ready;
};

#endif
