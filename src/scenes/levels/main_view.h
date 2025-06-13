#ifndef JM_LEVEL_ONE_H
#define JM_LEVEL_ONE_H

#include "src/types/font_types.h"
#include <stdbool.h>

struct main_view_t {
  struct label_t title;
};

bool main_view_init(struct main_view_t* level);
struct scene_t* main_view_prepare(struct main_view_t *s);
void main_view_free(struct main_view_t* level);

#endif
