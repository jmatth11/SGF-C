#include "button.h"
#include "src/types/components/button_types.h"
#include <SDL3/SDL_oldnames.h>

bool button_init(struct button_t *button, uint32_t id) {
  button->id = id;
  button->context = button;
  return true;
}

void button_render(SDL_Renderer *ren, void* context) {
  struct button_t *b = (struct button_t*)context;
  struct theme_t t = b->theme;
  SDL_SetRenderDrawColor(ren, t.color.r, t.color.g, t.color.b, t.color.a);
  SDL_RenderFillRect(ren, &b->rect);
}

struct render_interface button_get_render(struct button_t *button) {
  struct render_interface result = {0};
  result.context = button;
  result.render = button_render;
  return result;
}

void button_free(struct button_t *button) {
}
