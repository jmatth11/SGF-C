#ifndef GENERIC_STATE_TYPE_H
#define GENERIC_STATE_TYPE_H

#include "src/types/scene_types.h"
#include "src/types/win_types.h"

struct state_t {
  struct scene_t *current_scene;
  struct win_t win;
};

#endif
