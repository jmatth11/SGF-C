#include "text_input.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "gap_buffer.h"
#include "src/logic/base.h"
#include "src/logic/render.h"
#include "src/types/base.h"
#include "src/types/components/text_input.h"
#include "src/types/font_types.h"
#include "src/types/render_interface.h"
#include "unicode_str.h"
#include "utf8.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define TEXT_X_BUFFER 5
#define TEXT_Y_BUFFER 2

static uint8_t *char_arr_to_u8(const char *str, size_t len) {
  uint8_t *arr = malloc(sizeof(uint8_t) * len);
  for (size_t i = 0; i < len; ++i) {
    arr[i] = (uint8_t)str[i];
  }
  return arr;
}

static char *code_point_to_u8(const code_point_t *str, size_t len) {
  const size_t byte_len = code_point_to_utf8_len(str, len);
  char *result = malloc((sizeof(char) * byte_len) + 1);
  size_t result_i = 0;
  uint8_t buf[4] = {0};
  for (size_t i = 0; i < len; ++i) {
    const size_t write_n = utf8_write_code_point(buf, 4, 0, str[i]);
    for (size_t byte_idx = 0; byte_idx < write_n; ++byte_idx) {
      result[result_i] = buf[byte_idx];
      ++result_i;
    }
  }
  result[byte_len] = '\0';
  return result;
}

static SDL_FRect text_input_get_rect_or_default(struct text_input_t *ti) {
  SDL_FRect text_box_rect = ti->rect;
  int text_w = 0, text_h = 0;
  if (!TTF_GetTextSize(ti->text, &text_w, &text_h))
    return text_box_rect;

  if (ti->rect.h < 0) {
    if (text_h <= 0)
      text_h = 40;
    text_box_rect.h = text_h + (TEXT_Y_BUFFER * 2);
  }
  if (ti->rect.w < 0) {
    if (text_w < 120)
      text_w = 120;
    text_box_rect.w = text_w + (TEXT_X_BUFFER * 2);
  }
  return text_box_rect;
}

static float text_input_get_font_height(struct text_input_t *ti) {
  int text_w = 0, text_h = 0;
  if (!TTF_GetStringSize(ti->font->font, "W", 1, &text_w, &text_h))
    return 0;
  return text_h;
}

bool text_input_init(struct text_input_t *ti, struct font_t *font,
                     SDL_FRect rect) {
  if (ti == NULL)
    return false;
  if (font == NULL)
    return false;
  ti->id = base_id_generate();
  ti->font = font;
  ti->cursor_pos = 0;
  ti->focused = false;
  ti->text = TTF_CreateText(font->engine, font->font, "", 0);
  if (!TTF_SetTextColor(ti->text, 0x00, 0x00, 0x00, 0xff))
    return false;
  if (ti->text == NULL) {
    return false;
  }
  if (!gap_buffer_init(&ti->str, 5)) {
    return false;
  }
  ti->rect = rect;
  if (rect.h <= 0) {
    int text_w = 0, text_h = 0;
    if (!TTF_GetStringSize(ti->font->font, "W", 1, &text_w, &text_h)) {
      return false;
    }
    ti->rect.h = text_h + TEXT_Y_BUFFER;
  }
  return true;
}

bool text_input_point_in_rect(struct base_t *obj, SDL_FPoint p) {
  if (obj == NULL)
    return false;
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  SDL_FRect rect = text_input_get_rect_or_default(ti);
  return SDL_PointInRectFloat(&p, &rect);
}

static bool mouse_event(struct base_t *obj, SDL_Event *e) {
  if (e->type != SDL_EVENT_MOUSE_BUTTON_DOWN)
    return true;
  if (obj == NULL)
    return false;
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  const size_t gap_len = gap_buffer_get_len(&ti->str);
  // if not focused default to end of string.
  if (ti->focused == false) {
    ti->cursor_pos = gap_len;
    gap_buffer_move_cursor(&ti->str, ti->cursor_pos);
    return true;
  }
  // otherwise figure out where mouse clicked
  // get the relative position
  SDL_FPoint relative_mouse_pos = {.x = e->button.x - ti->rect.x,
                                   .y = e->button.y - ti->rect.y};
  TTF_SubString sub_string;
  if (!TTF_GetTextSubStringForPoint(ti->text, relative_mouse_pos.x,
                                    relative_mouse_pos.y, &sub_string)) {
    return false;
  }
  const size_t offset = sub_string.offset;
  if (gap_buffer_get_len(&ti->str) > 0) {
    // grab the byte offset since our gap_buffer is in codepoints
    size_t point_idx = codepoint_idx_from_byte_idx_char(
        ti->text->text, strlen(ti->text->text), offset);
    if (point_idx >= gap_len) {
      SDL_LogWarn(1,
                  "computed codepoint idx was out of range: idx:%lu, len:%lu\n",
                  point_idx, gap_len);
      // default to end of string
      point_idx = gap_len;
    }
    ti->cursor_pos = point_idx;
    gap_buffer_move_cursor(&ti->str, ti->cursor_pos);
  }
  return true;
}

bool text_input_text_event(struct base_t *obj, SDL_Event *e) {
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  bool modified = false;
  switch (e->type) {
  case SDL_EVENT_TEXT_INPUT: {
    modified = true;
    const size_t n = strlen(e->text.text);
    uint8_t *text = char_arr_to_u8(e->text.text, n);
    for (size_t i = 0; i < n;) {
      struct code_point point = utf8_next(text, n, i);
      i += octet_type_count(point.type);
      if (!gap_buffer_insert(&ti->str, point.val)) {
        free(text);
        return false;
      }
      ++ti->cursor_pos;
    }
    free(text);
    break;
  }
  case SDL_EVENT_KEY_DOWN: {
    if (e->key.key == SDLK_BACKSPACE) {
      modified = true;
      const size_t gap_len = gap_buffer_get_len(&ti->str);
      if (gap_len > 0 && ti->cursor_pos != 0) {
        if (!gap_buffer_delete(&ti->str)) {
          SDL_LogWarn(1, "could not perform backspace action.\n");
          return false;
        }
        --ti->cursor_pos;
      }
    }
    if (e->key.key == SDLK_LEFT) {
      if (ti->cursor_pos > 0) {
        ti->cursor_pos = ti->cursor_pos - 1;
        if (!gap_buffer_move_cursor(&ti->str, ti->cursor_pos)) {
          SDL_LogWarn(1, "could not perform move left action.\n");
          return false;
        }
      }
    }
    if (e->key.key == SDLK_RIGHT) {
      const size_t gap_len = gap_buffer_get_len(&ti->str);
      if (ti->cursor_pos < gap_len) {
        ti->cursor_pos = ti->cursor_pos + 1;
        if (!gap_buffer_move_cursor(&ti->str, ti->cursor_pos)) {
          SDL_LogWarn(1, "could not perform move right action.\n");
          return false;
        }
      }
    }
    if (e->key.key == SDLK_DELETE) {
      modified = true;
      const size_t gap_len = gap_buffer_get_len(&ti->str);
      if (ti->cursor_pos < gap_len) {
        ti->cursor_pos = ti->cursor_pos + 1;
        if (!gap_buffer_move_cursor(&ti->str, ti->cursor_pos)) {
          SDL_LogWarn(1, "could not perform move delete move action.\n");
          return false;
        }
        if (!gap_buffer_delete(&ti->str)) {
          SDL_LogWarn(1, "could not perform delete action.\n");
          return false;
        }
        ti->cursor_pos = ti->cursor_pos - 1;
      }
    }
    break;
  }
  }
  if (modified) {
    const size_t text_len = gap_buffer_get_len(&ti->str);
    code_point_t *points = gap_buffer_get_str(&ti->str);
    // if points is NULL the gap buffer is probably empty
    if (points == NULL) {
      TTF_SetTextString(ti->text, "", 0);
    } else {
      char *new_string = code_point_to_u8(points, text_len);
      free(points);
      // set string copies the given string
      TTF_SetTextString(ti->text, new_string, strlen(new_string));
      free(new_string);
    }
  }
  return true;
}

bool text_input_focus_event(struct base_t *obj, SDL_Event *e) {
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  SDL_Window *win = SDL_GetWindowFromEvent(e);
  if (win != NULL) {
    SDL_StartTextInput(win);
  }
  ti->focused = true;
  return true;
}
bool text_input_unfocus_event(struct base_t *obj, SDL_Event *e) {
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  SDL_Window *win = SDL_GetWindowFromEvent(e);
  if (win != NULL) {
    SDL_StopTextInput(win);
  }
  ti->focused = false;
  return true;
}

static bool text_input_render(struct base_t *obj, struct render_ctx_t *ctx) {
  if (!render_check_args(obj, ctx)) {
    return false;
  }
  SDL_Renderer *ren = ctx->ren;
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  int text_w = 0, text_h = 0;
  if (!TTF_GetTextSize(ti->text, &text_w, &text_h))
    return false;

  SDL_FRect text_box_rect = text_input_get_rect_or_default(ti);

  // TODO replace with theme values
  if (!SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff))
    return false;
  if (!SDL_RenderFillRect(ren, &text_box_rect))
    return false;
  if (!SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xff))
    return false;
  if (!SDL_RenderRect(ren, &text_box_rect))
    return false;

  int offset = 0;
  // TODO maybe need to store string in text input and use the TTF_Text
  // as the display text only.
  if (text_w > text_box_rect.w) {
    TTF_SubString sub_string;
    if (!TTF_GetTextSubStringForPoint(ti->text, text_h / 2, text_w - 8,
                                      &sub_string))
      return false;
    offset = sub_string.offset;
  }
  if (offset != 0) {
  }
  TTF_DrawRendererText(ti->text, text_box_rect.x + TEXT_X_BUFFER,
                       text_box_rect.y + TEXT_Y_BUFFER);
  if (ti->focused) {
    const size_t byte_offset = gap_buffer_byte_length(&ti->str, ti->cursor_pos);
    // TODO make cursor object
    SDL_SetRenderDrawColor(ren, 0xff, 0x00, 0x00, 0xff);
    int cursor_w = 0, cursor_h = 0;
    if (byte_offset > 0 &&
        !TTF_GetStringSize(ti->font->font, ti->text->text, byte_offset,
                           &cursor_w, &cursor_h)) {
      SDL_LogWarn(1, "could not get string size for text input.\n");
      return true;
    }
    if (text_h <= 0) {
      text_h = text_input_get_font_height(ti);
    }
    SDL_FRect cursor_rect = {
        .x = text_box_rect.x + cursor_w + ((float)TEXT_X_BUFFER / 2),
        .y = text_box_rect.y + TEXT_Y_BUFFER,
        .w = 1.5,
        .h = text_h - (TEXT_Y_BUFFER * 2),
    };
    SDL_RenderFillRect(ren, &cursor_rect);
  }
  return true;
}

struct events_t text_input_get_event(struct text_input_t *ti) {
  struct base_t b = {.parent = ti, .id = ti->id, .priority = 0};
  struct events_t result = {
      .base = b,
      .focus_event = text_input_focus_event,
      .unfocus_event = text_input_unfocus_event,
      .pointInRect = text_input_point_in_rect,
      .mouse_event = mouse_event,
      .text_event = text_input_text_event,
      .rectInRect = NULL,
  };
  return result;
}
static SDL_FRect text_input_get_viewable_rect(struct base_t *b,
                                              struct viewable_ctx_t *ctx) {
  (void)ctx;
  struct text_input_t *ti = (struct text_input_t *)b->parent;
  return text_input_get_rect_or_default(ti);
}

struct render_t text_input_get_render(struct text_input_t *ti) {
  struct base_t base = {.parent = ti, .id = ti->id, .priority = 0};
  return (struct render_t){
      .base = base,
      .render = text_input_render,
      .get_viewable_rect = text_input_get_viewable_rect,
  };
}

void text_input_free(struct text_input_t *ti) {
  if (ti == NULL)
    return;
  if (ti->text != NULL) {
    TTF_DestroyText(ti->text);
    ti->text = NULL;
  }
  gap_buffer_free(&ti->str);
  ti->font = NULL;
}
