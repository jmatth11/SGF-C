#include "start.h"

#include <stdbool.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"

#include "src/components/text_input.h"
#include "src/components/win.h"
#include "src/components/button.h"
#include "src/logic/scene.h"
#include "src/types/base.h"
#include "src/types/state.h"
#include "src/components/font.h"

#define start_text "start"
#define exit_text "exit"
#define title_text "Jumper"

static bool exit_clicked = false;

bool scene_one_init(struct scene_one_t *s) {
  (void)s;
  return true;
}

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
        exit_clicked = true;
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
  struct button_t* button = (struct button_t*)b->parent;
  return SDL_PointInRectFloat(&p, &button->rect);
}

static bool setup_buttons(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t*)scene->__internal;
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
    .x = (win_size.w/2.0) - (70.0/2.0),
    .y = (win_size.h/2.0) + (30.0/2.0),
  };
  local->start_btn.theme = (struct theme_t){
    .color = {.r=0x06, .g=0x66, .b=0xaa, .a=0xff},
  };
  if (!button_set_text(&local->start_btn, start_text, strlen(start_text))) {
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
    .color = {.r=0x06, .g=0x66, .b=0xaa, .a=0xff},
  };
  if (!button_set_text(&local->exit_btn, exit_text, strlen(exit_text))) {
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
    .base = {
      .parent = &local->start_btn,
      .id = local->start_btn.id,
    },
    .mouse_event = button_handler,
    .pointInRect = button_point_fn,
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

static bool load(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t*)scene->__internal;
  if (!label_init(&local->title, &state->font)) {
    SDL_LogError(1, "could not initialize title.\n");
    return false;
  }
  if (!label_set_text(&local->title, title_text, strlen(title_text))) {
    SDL_LogError(1, "could not set text for title.\n");
    return false;
  }
  SDL_Rect win_size = win_get_size(&state->win);
  SDL_Rect title_size = label_get_size(&local->title);
  // ignoring return
  (void)label_set_center_pos(&local->title, win_size.w/2, title_size.h + 20);
  if (!scene_add_child(scene, label_get_render(&local->title))) {
    return false;
  }
  if (!text_input_init(&local->text_input, &state->font, (SDL_FRect){.x=((double)win_size.w/2), .y=40, .w=120,.h=50})) {
    SDL_LogError(1, "Text input failed to initialize.\n");
    return false;
  }
  if (!scene_add_child(scene, text_input_get_render(&local->text_input))) {
    SDL_LogError(1, "text input could not be added to scene.\n");
    return false;
  }
  if (!scene_add_event_listener(scene, text_input_get_event(&local->text_input))) {
    SDL_LogError(1, "text input event could not be added to scene.\n");
    return false;
  }
  SDL_StartTextInput(state->win.win);
  if (!setup_buttons(scene, state)) {
    return false;
  }
  return true;
}

static bool unload(struct scene_t *scene, struct state_t *state) {
  (void)state;
  struct scene_one_t *local = (struct scene_one_t*)scene->__internal;
  scene_one_free(local);
  free(local);
  return true;
}

static bool update(struct scene_t *scene, struct state_t *state) {
  (void)scene;
  (void)state;
  return true;
}

static bool event(struct scene_t *scene, struct state_t *state, SDL_Event *event) {
  (void)scene;
  (void)event;
  if (exit_clicked) {
    state->app_state = SDL_APP_SUCCESS;
  }
  return true;
}

struct scene_t* scene_one_prepare(struct scene_one_t *s) {
  struct scene_t *result = scene_create();
  result->__internal = s;
  result->load = load;
  result->unload = unload;
  result->update = update;
  result->event = event;
  return result;
}

void scene_one_free(struct scene_one_t *s) {
  label_free(&s->title);
  button_free(&s->start_btn);
  button_free(&s->exit_btn);
}
