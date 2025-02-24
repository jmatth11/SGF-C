#ifndef GENERIC_STATE_TYPE_H
#define GENERIC_STATE_TYPE_H

#include "src/types/config_types.h"
#include "src/types/font_types.h"
#include "src/types/scene_types.h"
#include "src/types/win_types.h"

struct state_t {
  struct scene_t *current_scene;
  struct win_t win;
  // TODO replace with font_manager_t
  struct font_t font;
  struct config_t config;
};

#endif
