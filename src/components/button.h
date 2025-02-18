#ifndef GENERIC_BUTTON_H
#define GENERIC_BUTTON_H

#include "src/types/render_interface.h"
#include <stdbool.h>
#include <stdint.h>

struct button_t;

bool button_init(struct button_t *button, uint32_t id);
struct render_interface button_get_render(struct button_t *button);
void button_free(struct button_t *button);

#endif
