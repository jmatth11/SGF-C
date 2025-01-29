#ifndef GENERIC_STATE_H
#define GENERIC_STATE_H

#include "src/types/render_interface.h"
#include <stdbool.h>
#include <sys/cdefs.h>

struct state_t;

bool state_init(struct state_t* s) __nonnull((1));
bool state_add_render(struct state_t *s, struct render_interface ri);
void state_free(struct state_t* s) __nonnull((1));

#endif
