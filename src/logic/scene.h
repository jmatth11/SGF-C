#ifndef SGF_SCENE_H
#define SGF_SCENE_H

#include "SDL3/SDL_events.h"
#include "src/types/base.h"
#include <stdbool.h>

// forwarding
struct scene_t;

/**
 * Create a scene object.
 *
 * @return The newly created scene.
 */
struct scene_t* scene_create();

/**
 * Add child to scene.
 * The render_t objects passed in here get displayed to the screen in order of added.
 *
 * @return True for success, False otherwise.
 */
bool scene_add_child(struct scene_t* scene, struct render_t ren);
/**
 * Remove child from scene.
 *
 * @return True for success, False otherwise.
 */
bool scene_remove_child(struct scene_t* scene, uint64_t id);
/**
 * Add event listener to scene.
 * These are for SDL events.
 *
 * @return True for success, False otherwise.
 */
bool scene_add_event_listener(struct scene_t* scene, struct events_t e);
/**
 * Add collision object to scene.
 * Specific list of items with collision logic.
 *
 * @return True for success, False otherwise.
 */
bool scene_add_collision_listener(struct scene_t* scene, struct collision_event_t c);
// TODO add removal handlers as well

/**
 * Check current SDL_Event with the scene's list of event listeners.
 *
 * @return True for success, False otherwise.
 */
bool scene_check_events(struct scene_t* scene, SDL_Event *e);

/**
 * Destroy the given scene and its internals.
 *
 * @return True for success, False otherwise.
 */
void scene_destroy(struct scene_t **scene);

#endif
