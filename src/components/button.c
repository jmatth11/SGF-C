#include "button.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <stdbool.h>

#include "src/components/font.h"
#include "src/types/base.h"
#include "src/types/components/button_types.h"

bool button_init(struct button_t *button, uint32_t id, struct font_t *font) {
  button->id = id;
  button->context = button;
  return label_init(&button->label, font);
}

bool button_render(struct base_t *obj, SDL_Renderer *ren) {
  struct button_t *b = (struct button_t*)obj->parent;
  struct theme_t t = b->theme;
  if (!SDL_SetRenderDrawColor(ren, t.color.r, t.color.g, t.color.b, t.color.a)) {
    return false;
  }
  if (!SDL_RenderFillRect(ren, &b->rect)) {
    SDL_LogError(1, "could not render button %d\n", b->id);
    return false;
  }
  (void)label_set_center_pos(&b->label, b->rect.x + b->rect.w/2, b->rect.y + b->rect.h/2);
  return label_render(&b->label, NULL);
}

bool button_set_text(struct button_t *button, const char *str, size_t len) {
  if (!button->label.font) {
    SDL_LogError(1, "button had no viable font.\n");
    return false;
  }
  return label_set_text(&button->label, str, len);
}

struct render_t button_get_render(struct button_t *button) {
  struct render_t result = {0};
  result.base.id = button->id;
  result.base.parent = button;
  result.render = button_render;
  return result;
}

void button_free(struct button_t *button) {
  label_free(&button->label);
}
