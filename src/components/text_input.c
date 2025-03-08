#include "text_input.h"
#include "SDL3/SDL_rect.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "gap_buffer.h"
#include "src/types/font_types.h"
#include "src/types/components/text_input.h"
#include "unicode_str.h"
#include "utf8.h"
#include <stdint.h>

static uint8_t * char_arr_to_u8(const char *str, size_t len) {
  uint8_t *arr = malloc(sizeof(uint8_t)*len);
  for (size_t i = 0; i < len; ++i) {
    arr[i] = (uint8_t)str[i];
  }
  return arr;
}

bool text_input_init(struct text_input_t *ti, struct font_t *font, SDL_FRect rect) {
  if (ti == NULL) return false;
  if (font == NULL) return false;
  ti->font = font;
  ti->cursor_pos = 0;
  ti->text = TTF_CreateText(font->engine, font->font, "", 0);
  if (!TTF_SetTextColor(ti->text, 0x00, 0x00, 0x00, 0xff)) return false;
  if (ti->text == NULL) {
    return false;
  }
  if (!gap_buffer_init(&ti->str, 5)) {
    return false;
  }
  ti->rect = rect;
  return true;
}

bool text_input_point_in_rect(struct base_t *obj, SDL_FPoint p) {
  if (obj == NULL) return false;
  struct text_input_t *ti = (struct text_input_t*)obj->parent;
  return SDL_PointInRectFloat(&p, &ti->rect);
}

static bool mouse_event(struct base_t *obj, SDL_Event *e) {
  if (obj == NULL) return false;
  struct text_input_t *ti = (struct text_input_t*)obj->parent;
  SDL_FPoint mouse_pos = {.x = e->button.x, .y = e->button.y};
  // TODO get mouse position and move text input cursor
  TTF_SubString sub_string;
  if (!TTF_GetTextSubStringForPoint(ti->text, mouse_pos.x, mouse_pos.y, &sub_string)) return false;
  const size_t offset = sub_string.offset;
  return true;
}

bool text_input_text_event(struct base_t *obj, SDL_Event *e) {
  // TODO handle backspace and maybe handle enter key
  struct text_input_t *ti = (struct text_input_t*)obj->parent;
  const size_t n = strlen(e->text.text);
  uint8_t *text = char_arr_to_u8(e->text.text, n);
  for (size_t i = 0; i < n;) {
    struct code_point point = utf8_next(text, n, i);
    i += octet_type_count(point.type);
    if (!gap_buffer_insert(&ti->str, point.val)) {
      return false;
    }
  }
  return true;
}

static bool text_input_render(struct base_t *obj, SDL_Renderer *ren) {
  struct text_input_t *ti = (struct text_input_t*)obj->parent;

  // TODO replace with theme values
  if (!SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff)) return false;
  if (!SDL_RenderFillRect(ren, &ti->rect)) return false;
  if (!SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xff)) return false;
  if (!SDL_RenderFillRect(ren, &ti->rect)) return false;

  int w = 0, h = 0;
  if (!TTF_GetTextSize(ti->text, &w, &h)) return false;
  int offset = 0;
  // TODO maybe need to store string in text input and use the TTF_Text
  // as the display text only.
  if (w > ti->rect.w) {
    TTF_SubString sub_string;
    if (!TTF_GetTextSubStringForPoint(ti->text, h/2, w - 8, &sub_string)) return false;
    offset = sub_string.offset;
  }
  if (offset != 0) {
  }
  TTF_DrawRendererText(ti->text, ti->rect.x + 5, ti->rect.y + 2);

  return true;
}

struct render_t text_input_get_render(struct text_input_t *ti) {
  struct base_t base = {
    .parent = ti,
    .id = ti->id,
  };
  return (struct render_t){
    .base = base,
    .render = text_input_render,
  };
}

void text_input_free(struct text_input_t *ti) {
  if (ti == NULL) return;
  if (ti->text != NULL) {
    TTF_DestroyText(ti->text);
    ti->text = NULL;
  }
  gap_buffer_free(&ti->str);
  ti->font = NULL;
}
