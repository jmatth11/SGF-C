#ifndef SGF_BASE_FUNCS_H
#define SGF_BASE_FUNCS_H

#include <SDL3/SDL_events.h>
#include <stdbool.h>

#include <stdint.h>

// forward declare
struct events_t;

typedef uint32_t base_id;

/**
 * Generate a new unique base ID.
 */
base_id base_id_generate();

/**
 * Generate a new base structure with the given parent.
 * Generates with a new ID and priority set to 0.
 *
 * @return Newly generated base structure.
 */
struct base_t base_generate(void *parent);

/**
 * Default handler for checking mouse events.
 */
bool base_handle_mouse_event(struct events_t *e_handler, SDL_Event *e,
                             struct events_t **focused);

/**
 * Default handler for checking keyboard events.
 */
bool base_handle_keyboard_event(struct events_t *e_handler, SDL_Event *e);

#endif
