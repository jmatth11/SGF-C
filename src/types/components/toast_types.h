#ifndef SGF_TOAST_TYPES_H
#define SGF_TOAST_TYPES_H

#include "queue.h"
#include "src/types/base.h"
#include "src/types/font_types.h"
#include <stdbool.h>

enum toast_type_t {
  TOAST_SUCCESS = 0,
  TOAST_WARN,
  TOAST_ERROR,
};

enum toast_placement_t {
  TOAST_TOP_RIGHT,
  TOAST_TOP_LEFT,
  TOAST_TOP_CENTER,
  TOAST_BOTTOM_LEFT,
  TOAST_BOTTOM_CENTER,
  TOAST_BOTTOM_RIGHT,
};

struct toast_t {
  base_id id;
  enum toast_type_t type;
  enum toast_placement_t placement;
  struct label_t msg;
  SDL_FRect rect;
  SDL_FRect placement_rect;
};

struct toast_manager_t {
  struct simple_queue_t *toasts;
  struct toast_t *current_toast;
  struct scene_t *parent_scene;
  struct font_t *font;
  bool display_ready;
};

#endif
