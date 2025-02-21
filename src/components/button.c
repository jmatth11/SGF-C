#include "button.h"
#include "src/types/base.h"
#include "src/types/components/button_types.h"
#include <stdbool.h>

bool button_init(struct button_t *button, uint32_t id) {
  button->id = id;
  button->context = button;
  return true;
}

bool button_render(struct base_t *obj, SDL_Renderer *ren) {
  struct button_t *b = (struct button_t*)obj->parent;
  struct theme_t t = b->theme;
  if (!SDL_SetRenderDrawColor(ren, t.color.r, t.color.g, t.color.b, t.color.a)) {
    return false;
  }
  return SDL_RenderFillRect(ren, &b->rect);
}

struct render_t button_get_render(struct button_t *button) {
  struct render_t result = {0};
  result.base.id = button->id;
  result.base.parent = button;
  result.render = button_render;
  return result;
}

void button_free(struct button_t *button) {
}
