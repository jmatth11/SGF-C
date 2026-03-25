/**
 * @file scene.h
 * @brief Scene management functions.
 */

#ifndef SGF_SCENE_H
#define SGF_SCENE_H

#include "SDL3/SDL_events.h"
#include "../types/base.h"
#include <stdbool.h>

// forwarding
struct scene_t;

/**
 * @brief Create a new scene.
 *
 * @return Newly allocated scene, or NULL on failure.
 */
struct scene_t *scene_create(void);

/**
 * @brief Add a renderable child to the scene.
 *
 * Children are sorted by priority after being added.
 *
 * @param[out] scene Scene to add to.
 * @param[in] ren Renderable object to add.
 * @return true on success, false on failure.
 */
bool scene_add_child(struct scene_t *scene, struct render_t ren);

/**
 * @brief Remove a child from the scene by ID.
 *
 * @param[out] scene Scene to remove from.
 * @param[in] id ID of the child to remove.
 * @return true on success, false if not found.
 */
bool scene_remove_child(struct scene_t *scene, uint64_t id);

/**
 * @brief Add an event listener to the scene.
 *
 * Event listeners are sorted by priority after being added.
 *
 * @param[out] scene Scene to add to.
 * @param[in] e Event handler to add.
 * @return true on success, false on failure.
 */
bool scene_add_event_listener(struct scene_t *scene, struct events_t e);

/**
 * @brief Add a collision handler to the scene.
 *
 * @param[out] scene Scene to add to.
 * @param[in] c Collision handler to add.
 * @return true on success, false on failure.
 */
bool scene_add_collision_listener(struct scene_t *scene,
                                  struct collision_event_t c);

/**
 * @brief Process an SDL event through all event listeners.
 *
 * @param[in,out] scene Scene to process events for.
 * @param[in] e SDL event to handle.
 * @return true on success, false on failure.
 */
bool scene_check_events(struct scene_t *scene, SDL_Event *e);

/**
 * @brief Destroy a scene and free all resources.
 *
 * @param[in,out] scene Pointer to scene pointer to free.
 */
void scene_destroy(struct scene_t **scene);

#endif
