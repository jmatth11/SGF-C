/**
 * @file state.h
 * @brief Application state type definition.
 *
 * TODO: Replace font_t with font_manager_t for multiple font support.
 */

#ifndef GENERIC_STATE_TYPE_H
#define GENERIC_STATE_TYPE_H

#include "SDL3/SDL_init.h"
#include "../types/config_types.h"
#include "../types/font_types.h"
#include "../types/scene_types.h"
#include "../types/win_types.h"

/**
 * @brief Application state structure.
 *
 * Contains all global state for the application including the current scene,
 * window, and configuration.
 */
struct state_t {
  /** @brief Current application result code (continue, success, or failure). */
  enum SDL_AppResult app_state;
  /** @brief The currently active scene, or NULL if none. */
  struct scene_t *current_scene;
  /** @brief The queued next scene to switch to, or NULL if no switch pending. */
  struct scene_t *next_scene;
  /** @brief The main window and renderer. */
  struct win_t win;
  /** @brief Default font for UI components. */
  struct font_t font;
  /** @brief Application configuration. */
  struct config_t config;
  /** @brief User data pointer for custom application state. */
  void *user_data;
};

#endif
