#ifndef GENERIC_BUTTON_H
#define GENERIC_BUTTON_H

#include "src/types/base.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct button_t;
struct font_t;

bool button_init(struct button_t *button, uint32_t id, struct font_t *font);
struct render_t button_get_render(struct button_t *button);
bool button_set_text(struct button_t *button, const char *str, size_t len);
void button_free(struct button_t *button);

#endif
