#include "text_input.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "gap_buffer.h"
#include "src/types/font_types.h"
#include "src/types/components/text_input.h"
#include "unicode_str.h"

bool text_input_init(struct text_input_t *ti, struct font_t *font, SDL_FRect rect) {
  ti->font = font;
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

static bool text_input_render(struct base_t *obj, SDL_Renderer *ren) {
  struct text_input_t *ti = (struct text_input_t*)obj->parent;

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
