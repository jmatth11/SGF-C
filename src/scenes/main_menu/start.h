#ifndef SCENE_ONE_START_H
#define SCENE_ONE_START_H

#include <stdbool.h>

#include "src/types/components/button_types.h"
#include "src/types/components/text_input.h"
#include "src/types/font_types.h"
#include "src/types/scene_types.h"

struct scene_one_t {
  struct label_t title;
  struct button_t start_btn;
  struct button_t exit_btn;
  struct text_input_t text_input;
  bool exit_clicked;
};

bool scene_one_init(struct scene_one_t *s);
struct scene_t* scene_one_prepare(struct scene_one_t *s);
void scene_one_free(struct scene_one_t *s);

#endif
