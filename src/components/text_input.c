#include <stdio.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "text_input.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "gap_buffer.h"
#include "src/types/components/text_input.h"
#include "src/types/font_types.h"
#include "unicode_str.h"
#include "utf8.h"
#include <stdint.h>

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

bool text_input_init(struct text_input_t *ti, struct font_t *font,
                     SDL_FRect rect) {
  if (ti == NULL)
    return false;
  if (font == NULL)
    return false;
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
  return true;
}

bool text_input_point_in_rect(struct base_t *obj, SDL_FPoint p) {
  if (obj == NULL)
    return false;
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  return SDL_PointInRectFloat(&p, &ti->rect);
}

static bool mouse_event(struct base_t *obj, SDL_Event *e) {
  if (e->type != SDL_EVENT_MOUSE_BUTTON_DOWN)
    return true;
  if (obj == NULL)
    return false;
  struct text_input_t *ti = (struct text_input_t *)obj->parent;
  // TODO maybe need to redo this logic not sure if it entirely works
  // SDL_FPoint mouse_pos = {.x = e->button.x, .y = e->button.y};
  // TTF_SubString sub_string;
  // if (!TTF_GetTextSubStringForPoint(ti->text, mouse_pos.x, mouse_pos.y,
  //                                  &sub_string))
  //  return false;
  // const size_t offset = sub_string.offset;
  // TTF_SubString info;
  // if (!TTF_GetTextSubString(ti->text, 0, &info))
  //  return false;
  // size_t point_idx =
  //    codepoint_idx_from_byte_idx_char(ti->text->text, info.length, offset);
  const size_t gap_len = gap_buffer_get_len(&ti->str);
  size_t point_idx = gap_len;
  // if (point_idx >= gap_len) {
  //   SDL_LogWarn(1,
  //               "computed codepoint idx was out of range: idx:%lu,
  //               len:%lu\n", point_idx, gap_len);
  //   // default to end of string
  //   point_idx = gap_len;
  // }
  ti->cursor_pos = point_idx;
  gap_buffer_move_cursor(&ti->str, ti->cursor_pos);
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
      fprintf(stdout, "i=%lu; point=%u\n", i, point.val);
      fflush(stdout);
      if (!gap_buffer_insert(&ti->str, point.val)) {
        free(text);
        return false;
      }
    }
    free(text);
    break;
  }
  case SDL_EVENT_KEY_DOWN: {
    if (e->key.key == SDLK_BACKSPACE) {
      modified = true;
      if (!gap_buffer_delete(&ti->str)) {
        SDL_LogWarn(1, "could not perform backspace action.\n");
        return false;
      }
    }
    break;
  }
  }
  if (modified) {
    const size_t text_len = gap_buffer_get_len(&ti->str);
    code_point_t *points = gap_buffer_get_str(&ti->str);
    char *new_string = code_point_to_u8(points, text_len);
    fprintf(stdout, "new_string = \"%s\"\n", new_string);
    free(points);
    // set string copies the given string
    TTF_SetTextString(ti->text, new_string, strlen(new_string));
    free(new_string);
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

static bool text_input_render(struct base_t *obj, SDL_Renderer *ren) {
  struct text_input_t *ti = (struct text_input_t *)obj->parent;

  // TODO replace with theme values
  if (!SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff))
    return false;
  if (!SDL_RenderFillRect(ren, &ti->rect))
    return false;
  if (!SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xff))
    return false;
  if (!SDL_RenderRect(ren, &ti->rect))
    return false;

  int w = 0, h = 0;
  if (!TTF_GetTextSize(ti->text, &w, &h))
    return false;
  int offset = 0;
  // TODO maybe need to store string in text input and use the TTF_Text
  // as the display text only.
  if (w > ti->rect.w) {
    TTF_SubString sub_string;
    if (!TTF_GetTextSubStringForPoint(ti->text, h / 2, w - 8, &sub_string))
      return false;
    offset = sub_string.offset;
  }
  if (offset != 0) {
  }
  TTF_DrawRendererText(ti->text, ti->rect.x + 5, ti->rect.y + 2);
  if (ti->focused) {
    SDL_SetRenderDrawColor(ren, 0xff, 0x00, 0x00, 0xff);
    // TODO implement cursor
    SDL_FRect cursor_rect = {
        .x = ti->rect.x + w,
        .y = ti->rect.y + 5,
        .w = 5,
        .h = h,
    };
    SDL_RenderFillRect(ren, &cursor_rect);
  }
  return true;
}

struct events_t text_input_get_event(struct text_input_t *ti) {
  struct base_t b = {
      .parent = ti,
      .id = ti->id,
  };
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
  if (ti == NULL)
    return;
  if (ti->text != NULL) {
    TTF_DestroyText(ti->text);
    ti->text = NULL;
  }
  gap_buffer_free(&ti->str);
  ti->font = NULL;
}
