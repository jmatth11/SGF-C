/**
 * @file base.h
 * @brief Base object and ID generation functions.
 */

#ifndef SGF_BASE_FUNCS_H
#define SGF_BASE_FUNCS_H

#include <SDL3/SDL_events.h>
#include <stdbool.h>

#include <stdint.h>

// forward declare
struct events_t;

/**
 * @brief Type alias for base object IDs.
 */
typedef uint32_t base_id;

/**
 * @brief Generate a new unique base ID.
 *
 * Each call returns an incrementing unique ID.
 *
 * @return New unique base_id.
 */
base_id base_id_generate(void);

/**
 * @brief Create a base structure with a new ID.
 *
 * @param[in] parent Pointer to the parent object.
 * @return New base_t with unique ID and priority 0.
 */
struct base_t base_generate(void *parent);

/**
 * @brief Process a mouse event for an event handler.
 *
 * Checks if the event position is within the handler's bounds
 * and calls the handler's mouse event function if so.
 *
 * @param[in,out] e_handler Event handler to process.
 * @param[in] e SDL event data.
 * @param[out] focused Set to e_handler if it should gain focus.
 * @return true on success, false on failure.
 */
bool base_handle_mouse_event(struct events_t *e_handler, SDL_Event *e,
                             struct events_t **focused);

/**
 * @brief Process a keyboard/text event for an event handler.
 *
 * @param[in] e_handler Event handler to process.
 * @param[in] e SDL event data.
 * @return true on success, false on failure.
 */
bool base_handle_keyboard_event(struct events_t *e_handler, SDL_Event *e);

#endif
