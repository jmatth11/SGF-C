#include "button.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <stdbool.h>

#include "src/components/font.h"
#include "src/logic/base.h"
#include "src/types/base.h"
#include "src/types/components/button_types.h"

#define BUTTON_SIDE_PADDING 3
#define BUTTON_TOP_PADDING 2

SDL_FRect button_get_rect(struct button_t *button) {
  SDL_FRect rect = button->rect;
  int text_w = 0, text_h = 0;
  if (button->label.text == NULL || !TTF_GetTextSize(button->label.text, &text_w, &text_h)) {
    return rect;
  }
  if (rect.h < 0) {
    if (text_h < 0) {
      text_h = 40;
    }
    rect.h = text_h + (BUTTON_TOP_PADDING*2);
  }
  if (rect.w < 0) {
    if (text_w < 0) {
      text_w = 80;
    }
    rect.w = text_w + (BUTTON_SIDE_PADDING*2);
  }
  if (button->center) {
    rect.x -= rect.w/2;
    rect.y -= rect.h/2;
  }
  return rect;
}

bool button_init(struct button_t *button, struct font_t *font) {
  button->id = base_id_generate();
  button->context = button;
  button->center = false;
  return label_init(&button->label, font);
}

bool button_render(struct base_t *obj, SDL_Renderer *ren) {
  struct button_t *b = (struct button_t*)obj->parent;
  SDL_FRect rect = button_get_rect(b);
  struct theme_t t = b->theme;
  if (!SDL_SetRenderDrawColor(ren, t.color.r, t.color.g, t.color.b, t.color.a)) {
    return false;
  }
  if (!SDL_RenderFillRect(ren, &rect)) {
    SDL_LogError(1, "could not render button %lu\n", b->id);
    return false;
  }
  (void)label_set_center_pos(&b->label, rect.x + rect.w/2, rect.y + rect.h/2);
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
