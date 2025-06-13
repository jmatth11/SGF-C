#ifndef GENERIC_STATE_TYPE_H
#define GENERIC_STATE_TYPE_H

#include "SDL3/SDL_init.h"
#include "src/types/config_types.h"
#include "src/types/font_types.h"
#include "src/types/scene_types.h"
#include "src/types/user_data.h"
#include "src/types/win_types.h"

struct state_t {
  enum SDL_AppResult app_state;
  struct scene_t *current_scene;
  struct scene_t *next_scene;
  struct win_t win;
  // TODO replace with font_manager_t
  struct font_t font;
  struct config_t config;
  struct user_data *user_data;
};

#endif
