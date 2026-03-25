/**
 * @file scene_types.h
 * @brief Scene type definitions and function pointer types.
 */

#ifndef SGF_SCENE_TYPES_H
#define SGF_SCENE_TYPES_H

#include "SDL3/SDL_events.h"
#include <stdbool.h>

#include "../types/base.h"

struct scene_t;
struct state_t;
struct world_t;

/**
 * @brief Scene load function type.
 *
 * Called when a scene becomes the active scene.
 *
 * @param scene The scene being loaded.
 * @param state The application state.
 * @return true on success, false on failure.
 */
typedef bool (*load_fn)(struct scene_t *scene, struct state_t *state);

/**
 * @brief Scene update function type.
 *
 * Called every frame to update scene logic.
 *
 * @param scene The scene to update.
 * @param state The application state.
 * @param deltatime Time elapsed since last update in seconds.
 * @return true on success, false on failure.
 */
typedef bool (*update_fn)(struct scene_t *scene, struct state_t *state,
                          double deltatime);

/**
 * @brief Scene event handler function type.
 *
 * Called for each SDL event to handle input.
 *
 * @param scene The scene receiving the event.
 * @param state The application state.
 * @param event The SDL event data.
 * @return true on success, false on failure.
 */
typedef bool (*event_fn)(struct scene_t *scene, struct state_t *state,
                         SDL_Event *event);

/**
 * @brief Scene unload function type.
 *
 * Called when a scene is being replaced by another scene.
 *
 * @param scene The scene being unloaded.
 * @param state The application state.
 * @return true on success, false on failure.
 */
typedef bool (*unload_fn)(struct scene_t *scene, struct state_t *state);

/**
 * @brief Scene structure containing all data for a game/screen state.
 *
 * A scene manages its own renderable children, event handlers, and collision
 * objects. Scenes have a lifecycle with load, update, event, and unload phases.
 */
struct scene_t {
  /** @brief Internal data pointer for scene-specific data. */
  void *__internal;
  /** @brief Array of renderable child objects. */
  render_array children;
  /** @brief Array of event handlers. */
  events_array events;
  /** @brief Array of collision detection objects. */
  collision_array collisions;
  /** @brief Currently focused event element, or NULL if none. */
  struct events_t *focused_el;
  /** @brief World context for coordinate transformation. NULL if not used. */
  struct world_t *world;

  /** @brief Called when scene becomes active. */
  load_fn load;
  /** @brief Called every frame to update logic. */
  update_fn update;
  /** @brief Called to handle SDL events. */
  event_fn event;
  /** @brief Called when scene is being replaced. */
  unload_fn unload;
};

#endif
