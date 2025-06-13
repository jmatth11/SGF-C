#ifndef SGF_BASE_FUNCS_H
#define SGF_BASE_FUNCS_H

#include <stdbool.h>
#include <SDL3/SDL_events.h>

#include <stdint.h>

typedef uint32_t base_id;

base_id base_id_generate();

struct events_t;

bool base_handle_mouse_event(struct events_t *e_handler, SDL_Event *e, struct events_t **focused);
bool base_handle_keyboard_event(struct events_t *e_handler, SDL_Event *e);

#endif
