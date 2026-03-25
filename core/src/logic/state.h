/**
 * @file state.h
 * @brief Application state management functions.
 */

#ifndef GENERIC_STATE_H
#define GENERIC_STATE_H

#include "../types/render_interface.h"
#include <stdbool.h>

struct state_t;
struct scene_t;

/**
 * @brief Initialize the application state.
 *
 * Creates window, initializes font, and sets up default configuration.
 *
 * @param[out] s State structure to initialize.
 * @return true on success, false on failure.
 */
bool state_init(struct state_t *s);

/**
 * @brief Queue a scene switch.
 *
 * The switch will occur on the next update cycle.
 *
 * @param[out] s Application state.
 * @param[in] scene New scene to switch to, or NULL to exit.
 * @return true always.
 */
bool state_switch_scene(struct state_t *s, struct scene_t *scene);

/**
 * @brief Free application state resources.
 *
 * @param[out] s State to free.
 */
void state_free(struct state_t *s);

#endif
