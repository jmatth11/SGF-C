#ifndef GENERIC_STATE_H
#define GENERIC_STATE_H

#include "src/types/render_interface.h"
#include <stdbool.h>

struct state_t;
struct scene_t;

/**
 * Initialize the application state.
 *
 * @return True for success, false otherwise.
 */
bool state_init(struct state_t *s);
/**
 * Queue the state to switch to a different scene on next update.
 *
 * @return True for success, false otherwise.
 */
bool state_switch_scene(struct state_t *s, struct scene_t *scene);
/**
 * Free the state object.
 */
void state_free(struct state_t *s);

#endif
