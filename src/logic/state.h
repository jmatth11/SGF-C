#ifndef GENERIC_STATE_H
#define GENERIC_STATE_H

#include "src/types/render_interface.h"
#include <stdbool.h>

struct state_t;
struct scene_t;

bool state_init(struct state_t* s);
bool state_switch_scene(struct state_t *s, struct scene_t *scene);
void state_free(struct state_t* s);

#endif
