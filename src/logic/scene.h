#ifndef SGF_SCENE_H
#define SGF_SCENE_H

#include "src/types/base.h"
#include <stdbool.h>

struct scene_t;

struct scene_t* scene_create();

bool scene_add_child(struct scene_t* scene, struct render_t ren);
bool scene_add_event_listener(struct scene_t* scene, struct events_t e);
bool scene_add_collision_listener(struct scene_t* scene, struct collision_event_t c);
// TODO add removal handlers as well

void scene_destroy(struct scene_t **scene);

#endif
