#include <stdio.h>
#include "src/components/win.h"
#include "start.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "src/components/button.h"
#include "src/logic/scene.h"
#include "src/types/state.h"
#include "src/components/font.h"

#define start_text "start"
#define exit_text "exit"
#define title_text "Jumper"

bool scene_one_init(struct scene_one_t *s) {
  (void)s;
  return true;
}

static bool load(struct scene_t *scene, struct state_t *state) {
  SDL_Log("entering load function.\n");
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
  if (!button_init(&local->start_btn, 1, &state->font)) {
    return false;
  }
  if (!button_init(&local->exit_btn, 2, &state->font)) {
    return false;
  }
  local->start_btn.rect = (SDL_FRect){
    .h = 40,
    .w = 70,
    .x = (win_size.w/2.0) - 70.0,
    .y = (win_size.h/2.0) + 30.0,
  };
  local->start_btn.theme = (struct theme_t){
    .color = {.r=0x06, .g=0x66, .b=0xaa, .a=0xff},
  };
  if (!button_set_text(&local->start_btn, start_text, strlen(start_text))) {
    fprintf(stderr, "could not add text to button %d\n", local->start_btn.id);
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
    fprintf(stderr, "could not add text to button %d\n", local->exit_btn.id);
    return false;
  }
  if (!scene_add_child(scene, label_get_render(&local->title))) {
    return false;
  }
  if (!scene_add_child(scene, button_get_render(&local->start_btn))) {
    return false;
  }
  if (!scene_add_child(scene, button_get_render(&local->exit_btn))) {
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
  SDL_Log("entering update function\n");
  (void)scene;
  (void)state;
  return true;
}

static bool event(struct scene_t *scene, struct state_t *state, SDL_Event *event) {
  (void)state;
  struct scene_one_t *local = (struct scene_one_t*)scene->__internal;
  struct button_t buttons[2] = {local->start_btn, local->exit_btn};
  switch (event->button.type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        SDL_Log("event mouse button");
        SDL_FPoint p = { .x = event->button.x, .y = event->button.y };
        SDL_Log("x=%f, y=%f", p.x, p.y);
        for (int i = 0; i < 2; ++i) {
          SDL_FRect rect = buttons[i].rect;
          if (SDL_PointInRectFloat(&p, &rect)) {
            SDL_Log("Button pressed with ID: %d", buttons[i].id);
          }
        }
      break;
    }
    default:
      break;
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
