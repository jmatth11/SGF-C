#include "toast.h"
#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "queue.h"
#include "src/components/font.h"
#include "src/logic/base.h"
#include "src/logic/render.h"
#include "src/logic/scene.h"
#include "src/types/base.h"
#include "src/types/color.h"
#include "src/types/components/toast_types.h"
#include "src/types/font_types.h"
#include <SDL3/SDL_timer.h>

static bool toast_init(struct toast_t *t, struct font_t *font) {
  t->type = TOAST_ERROR;
  t->placement = TOAST_BOTTOM_RIGHT;
  t->id = base_id_generate();
  t->rect = (SDL_FRect){0, 0, 0, 0};
  t->placement_rect = (SDL_FRect){0, 0, 0, 0};
  if (!label_init(&t->msg, font)) {
    return false;
  }
  return true;
}
/**
 * Create a toast structure with the given data.
 *
 * @param font The font to use.
 * @param text The text to display.
 * @param length The length of the text.
 * @param _type The toast type. See enum toast_type_t. Invalid types default to
 * error type.
 * @param _placement The default placement. See enum toast_placement_t. Invalid
 * placements will default to bottom right.
 * @param window_size The rect size of the window to be placed on.
 * If NULL the renderer safe area size will be used.
 * @return True on success, false otherwise.
 */
struct toast_t *toast_create(struct font_t *font, const char *text,
                             size_t length, int _type, int _placement,
                             SDL_FRect *window_size) {
  struct toast_t *t = malloc(sizeof(struct toast_t));
  toast_init(t, font);
  if (!toast_set_message(t, text, length)) {
    return false;
  }
  if (!toast_set_type(t, _type)) {
    return false;
  }
  if (!toast_set_placement(t, _placement, window_size)) {
    return false;
  }
  return t;
}

/**
 * Set the message of the toast structure.
 *
 * @param t The toast structure.
 * @param text The message.
 * @param length The length of the message.
 * @return True on success, false otherwise.
 */
bool toast_set_message(struct toast_t *t, const char *text, size_t length) {
  return label_set_text(&t->msg, text, length);
}
/**
 * Set the toast's type.
 *
 * @param t The toast structure.
 * @param _type The type. See enum toast_type_t.
 * @return True on success, false otherwise.
 */
bool toast_set_type(struct toast_t *t, int _type) {
  enum toast_type_t value = TOAST_ERROR;
  switch (_type) {
  case TOAST_SUCCESS:
  case TOAST_WARN:
  case TOAST_ERROR:
    value = _type;
    break;
  default:
    value = TOAST_ERROR;
    break;
  }
  t->type = value;
  return true;
}

/**
 * Set the placement of the toast.
 *
 * @param t The toast structure.
 * @param _placement The default placement. See enum toast_placement_t. Invalid
 * placements will default to bottom right.
 * @return True on success, false otherwise.
 */
bool toast_set_placement(struct toast_t *t, int _placement,
                         SDL_FRect *window_size) {
  enum toast_placement_t value = TOAST_BOTTOM_RIGHT;
  if (_placement < TOAST_BOTTOM_RIGHT) {
    value = _placement;
  }
  t->placement = value;
  if (window_size != NULL) {
    t->placement_rect = *window_size;
  }
  return true;
}

static SDL_Color toast_color(struct toast_t *t) {
  switch (t->type) {
  case TOAST_SUCCESS:
    return COLOR_GREEN;
  case TOAST_WARN:
    return COLOR_YELLOW;
  default:
    return COLOR_RED;
  }
}
static void toast_determine_placement(struct toast_t *t, SDL_Rect placement,
                                      SDL_FRect *dest) {
  const float buffer = 5;
  SDL_FPoint dest_center = {
      .x = dest->w * 0.5,
      .y = dest->h * 0.5,
  };
  SDL_FPoint placement_center = {
      .x = placement.w * 0.5,
      .y = placement.h * 0.5,
  };
  switch (t->placement) {
  case TOAST_BOTTOM_RIGHT: {
    dest->x = placement.w - dest->w - buffer;
    dest->y = placement.h - dest->h - buffer;
    break;
  }
  case TOAST_BOTTOM_LEFT: {
    dest->x = placement.x + buffer;
    dest->y = placement.h - dest->h - buffer;
    break;
  }
  case TOAST_BOTTOM_CENTER: {
    dest->x = placement_center.x - dest_center.x;
    dest->y = placement.h - dest->h - buffer;
    break;
  }
  case TOAST_TOP_RIGHT: {
    dest->x = placement.w - dest->w - buffer;
    dest->y = placement.y + buffer;
    break;
  }
  case TOAST_TOP_LEFT: {
    dest->x = placement.x + buffer;
    dest->y = placement.y + buffer;
    break;
  }
  case TOAST_TOP_CENTER: {
    dest->x = placement_center.x - dest_center.x;
    dest->y = placement.y + buffer;
    break;
  }
  }
}

static bool toast_render_fn(struct base_t *obj, SDL_Renderer *ren) {
  struct toast_t *t = (struct toast_t *)obj->parent;
  SDL_Rect placement_rect = (SDL_Rect){
      .x = t->placement_rect.x,
      .y = t->placement_rect.y,
      .h = t->placement_rect.h,
      .w = t->placement_rect.w,
  };
  if (placement_rect.h == 0 || placement_rect.w == 0) {
    SDL_GetRenderSafeArea(ren, &placement_rect);
  }
  SDL_Color background_color = toast_color(t);
  background_color.a = 0x99;

  SDL_FRect rect = t->rect;
  if (rect.h == 0 || rect.w == 0) {
    rect.h = 40;
    rect.w = 70;
  }
  const SDL_Rect label_size = label_get_size(&t->msg);
  // TODO experiment with wrapping
  if (rect.h < label_size.h || rect.w < label_size.w) {
    rect.h = label_size.h + 30;
    rect.w = label_size.w + 10;
  }
  toast_determine_placement(t, placement_rect, &rect);
  if (!render_transparent_fill_rect(ren, background_color, &rect)) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "failed to draw background of toast.\n");
  }
  SDL_FPoint label_center = {
    .x = rect.x + (rect.w * 0.5),
    .y = rect.y + (rect.h * 0.5),
  };
  (void)label_set_center_pos(&t->msg, label_center.x, label_center.y);
  if (!label_render(&t->msg, ren)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error rendering toast label\n");
    return false;
  }
  return true;
}

struct render_t toast_prepare_render(struct toast_t *t) {
  struct render_t result;
  struct base_t base = {
      .id = t->id,
      .parent = t,
  };
  result.base = base;
  result.render = toast_render_fn;
  return result;
}

void toast_destroy(struct toast_t **t) {
  if (t == NULL || *t == NULL) {
    return;
  }
  label_free(&(*t)->msg);
  free(*t);
  *t = NULL;
}

/* Toast Manager */

struct toast_manager_t *toast_manager_create() {
  struct toast_manager_t *result = malloc(sizeof(struct toast_manager_t));
  result->current_toast = NULL;
  result->parent_scene = NULL;
  result->display_ready = true;
  result->toasts = simple_queue_create();
  if (result->toasts == NULL) {
    toast_manager_destroy(&result);
    return NULL;
  }
  return result;
}
bool toast_manager_push(struct toast_manager_t *tm, struct toast_t *toast) {
  return simple_queue_push(tm->toasts, toast);
}

static Uint32 toast_manager_toggle_display(void *userdata, SDL_TimerID timerID,
                                           Uint32 interval) {
  (void)timerID;
  (void)interval;
  struct toast_manager_t *tm = (struct toast_manager_t *)userdata;
  tm->display_ready = true;
  return 0;
}

static Uint32 toast_manager_cb(void *userdata, SDL_TimerID timerID,
                               Uint32 interval) {
  (void)timerID;
  (void)interval;
  struct toast_manager_t *tm = (struct toast_manager_t *)userdata;
  if (!scene_remove_child(tm->parent_scene, tm->current_toast->id)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "error removing toast from scene.\n");
    return 0;
  }
  toast_destroy(&tm->current_toast);
  tm->current_toast = NULL;
  SDL_AddTimer(SDL_MS_PER_SECOND * 2, toast_manager_toggle_display, tm);
  return 0;
}

bool toast_manager_update(struct toast_manager_t *tm, struct scene_t *scene) {
  if (!tm->display_ready) {
    return true;
  }
  struct scene_t *current_scene = scene;
  if (current_scene == NULL) {
    current_scene = tm->parent_scene;
  } else if (tm->parent_scene != NULL) {
    tm->parent_scene = scene;
  }
  if (tm->parent_scene == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Scene and parent_scene of toast manager was NULL.\n");
    return false;
  }
  struct toast_t *out = NULL;
  if (!simple_queue_pop(tm->toasts, (void **)&out)) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "error getting toast from queue.\n");
    return false;
  }
  if (out == NULL) {
    return true;
  }
  tm->current_toast = out;
  if (!scene_add_child(current_scene, toast_prepare_render(out))) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "could not add toast to scene.\n");
    return false;
  }
  tm->display_ready = false;
  return SDL_AddTimer(SDL_MS_PER_SECOND * 10, toast_manager_cb, tm) != 0;
}

void toast_manager_destroy(struct toast_manager_t **tm) {
  if (tm == NULL || *tm == NULL) {
    return;
  }
  const size_t q_len = simple_queue_len((*tm)->toasts);
  for (size_t i = 0; i < q_len; ++i) {
    struct toast_t *tmp = NULL;
    simple_queue_pop((*tm)->toasts, (void**)&tmp);
    if (tmp != NULL) {
      toast_destroy(&tmp);
    }
  }
  simple_queue_destroy(&(*tm)->toasts);
  free(*tm);
  *tm = NULL;
}
