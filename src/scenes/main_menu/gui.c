#include "gui.h"
#include "SDL3/SDL_log.h"
#include "src/components/button.h"
#include "src/components/font.h"
#include "src/components/win.h"
#include "src/logic/scene.h"
#include "start.h"

#define CONNECT_TEXT "CONNECT"
#define EXIT_TEXT "EXIT"
#define TITLE_TEXT "DB LISTENER"

static struct scene_one_t *delegate = NULL;

static bool button_handler(struct base_t *obj, SDL_Event *e) {
  (void)e;
  switch (obj->id) {
  case 1: {
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      SDL_Log("clicked start\n");
    }
    break;
  }
  case 2: {
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      SDL_Log("clicked exit\n");
      if (delegate != NULL) {
        delegate->exit_clicked = true;
      }
    }
    break;
  }
  default: {
    break;
  }
  }
  return true;
}

static bool button_point_fn(struct base_t *b, SDL_FPoint p) {
  struct button_t *button = (struct button_t *)b->parent;
  return SDL_PointInRectFloat(&p, &button->rect);
}

static bool setup_buttons(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  if (!button_init(&local->start_btn, 1, &state->font)) {
    return false;
  }
  if (!button_init(&local->exit_btn, 2, &state->font)) {
    return false;
  }
  SDL_Rect win_size = win_get_size(&state->win);
  local->start_btn.rect = (SDL_FRect){
      .h = 40,
      .w = 70,
      .x = (win_size.w / 2.0) - (70.0 / 2.0),
      .y = (win_size.h / 2.0) + (30.0 / 2.0),
  };
  local->start_btn.theme = (struct theme_t){
      .color = {.r = 0x06, .g = 0x66, .b = 0xaa, .a = 0xff},
  };
  if (!button_set_text(&local->start_btn, CONNECT_TEXT, strlen(CONNECT_TEXT))) {
    SDL_LogError(1, "could not add text to button %d\n", local->start_btn.id);
    return false;
  }
  local->exit_btn.rect = (SDL_FRect){
      .h = 40,
      .w = 70,
      .x = local->start_btn.rect.x,
      .y = local->start_btn.rect.y + 60,
  };
  local->exit_btn.theme = (struct theme_t){
      .color = {.r = 0x06, .g = 0x66, .b = 0xaa, .a = 0xff},
  };
  if (!button_set_text(&local->exit_btn, EXIT_TEXT, strlen(EXIT_TEXT))) {
    SDL_LogError(1, "could not add text to button %d\n", local->exit_btn.id);
    return false;
  }
  if (!scene_add_child(scene, button_get_render(&local->start_btn))) {
    return false;
  }
  if (!scene_add_child(scene, button_get_render(&local->exit_btn))) {
    return false;
  }
  struct events_t button_event = {
      .base =
          {
              .parent = &local->start_btn,
              .id = local->start_btn.id,
          },
      .mouse_event = button_handler,
      .pointInRect = button_point_fn,
      .rectInRect = NULL,
      .text_event = NULL,
      .focus_event = NULL,
      .unfocus_event = NULL,
  };
  if (!scene_add_event_listener(scene, button_event)) {
    SDL_LogError(1, "adding event listener failed\n");
    return false;
  }
  button_event.base.parent = &local->exit_btn;
  button_event.base.id = local->exit_btn.id;
  if (!scene_add_event_listener(scene, button_event)) {
    SDL_LogError(1, "adding event listener failed\n");
    return false;
  }
  return true;
}

static bool setup_title(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  if (!label_init(&local->title, &state->font)) {
    SDL_LogError(1, "could not initialize title.\n");
    return false;
  }
  if (!label_set_text(&local->title, TITLE_TEXT, strlen(TITLE_TEXT))) {
    SDL_LogError(1, "could not set text for title.\n");
    return false;
  }
  SDL_Rect win_size = win_get_size(&state->win);
  SDL_Rect title_size = label_get_size(&local->title);
  (void)label_set_center_pos(&local->title, win_size.w / 2, title_size.h + 20);
  if (!scene_add_child(scene, label_get_render(&local->title))) {
    return false;
  }
  return true;
}

bool setup_gui(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  delegate = local;
  if (!setup_buttons(scene, state)) {
    SDL_LogWarn(1, "failed button setup for main menu.\n");
    return false;
  }
  return true;
}
