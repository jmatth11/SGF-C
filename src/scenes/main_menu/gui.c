#include "gui.h"
#include "SDL3/SDL_log.h"
#include "src/components/button.h"
#include "src/components/font.h"
#include "src/components/loading_icon.h"
#include "src/components/text_input.h"
#include "src/components/win.h"
#include "src/logic/scene.h"
#include "src/scenes/main_menu/logic.h"
#include "start.h"

#define CONNECT_TEXT "CONNECT"
#define EXIT_TEXT "EXIT"
#define TITLE_TEXT "DB LISTENER"

static struct scene_one_t *delegate = NULL;

static bool button_handler(struct base_t *obj, SDL_Event *e) {
  if (delegate == NULL) return false;
  if (delegate->loading) return true;
  switch (obj->id) {
  case 1: {
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (validate_user_data(&delegate->host_url, &delegate->user_data)) {
          delegate->loading = true;
        } else {
          SDL_Log("user data is invalid!\n");
        }
    }
    break;
  }
  case 2: {
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      SDL_Log("clicked exit\n");
      delegate->exit_clicked = true;
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
  SDL_FRect rect = button_get_rect(button);
  return SDL_PointInRectFloat(&p, &rect);
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
      .h = -1,
      .w = -1,
      .x = (win_size.w / 2.0),
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
      .h = -1,
      .w = -1,
      .x = local->start_btn.rect.x,
      .y = local->start_btn.rect.y + 60,
  };
  local->exit_btn.theme = (struct theme_t){
      .color = {.r = 0x06, .g = 0x66, .b = 0xaa, .a = 0xff},
  };
  local->start_btn.center = true;
  local->exit_btn.center = true;
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
  // TODO move to it's own function
  if (!loading_icon_init(&local->loading_icon,
                    state->win.ren, "./resources/icons/loading.png")) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to load loading image");
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

static bool setup_text_input(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  local->host_url.id = 12;
  SDL_Rect win_size = win_get_size(&state->win);
  SDL_Rect title_size = label_get_size(&local->title);
  if (!text_input_init(&local->host_url, &state->font,
                       (SDL_FRect){
                           .x = ((double)win_size.w / 2) - 60,
                           .y = title_size.h + 60,
                           .w = -1, // default to 120
                           .h = -1, // default to font size
                       })) {
    SDL_LogError(1, "Text input failed to initialize.\n");
    return false;
  }
  if (!scene_add_child(scene, text_input_get_render(&local->host_url))) {
    SDL_LogError(1, "text input could not be added to scene.\n");
    return false;
  }
  if (!scene_add_event_listener(scene,
                                text_input_get_event(&local->host_url))) {
    SDL_LogError(1, "text input event could not be added to scene.\n");
    return false;
  }
  return true;
}

bool setup_gui(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  delegate = local;
  if (!setup_title(scene, state)) {
    SDL_LogWarn(1, "failed title setup for main menu.\n");
    return false;
  }
  if (!setup_text_input(scene, state)) {
    SDL_LogWarn(1, "failed text input setup for main menu.\n");
    return false;
  }
  if (!setup_buttons(scene, state)) {
    SDL_LogWarn(1, "failed button setup for main menu.\n");
    return false;
  }
  return true;
}
