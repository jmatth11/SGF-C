#ifndef SCENE_ONE_START_H
#define SCENE_ONE_START_H

#include "src/types/components/button_types.h"
#include "src/types/scene_types.h"
#include <stdbool.h>

struct scene_one_t {
  struct button_t start_btn;
  struct button_t exit_btn;
};

bool scene_one_init(struct scene_one_t *s);
struct scene_t* scene_one_prepare(struct scene_one_t *s);
void scene_one_free(struct scene_one_t *s);

#endif
