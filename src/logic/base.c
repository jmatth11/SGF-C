#include <stdatomic.h>
#include "base.h"
#include "src/types/base.h"
#include <SDL3/SDL_log.h>

static atomic_ulong global_id = 0;

base_id base_id_generate() {
  return atomic_fetch_add(&global_id, 1);
}

bool base_handle_mouse_event(struct events_t *e_handler, SDL_Event *e,
                             struct events_t **focused) {
  SDL_FPoint mouse_pos = {.x = e->button.x, .y = e->button.y};
  if (e_handler->pointInRect != NULL &&
      e_handler->pointInRect(&e_handler->base, mouse_pos)) {
    *focused = e_handler;
    if (e_handler->mouse_event != NULL && !e_handler->mouse_event(&e_handler->base, e)) {
      SDL_LogWarn(1, "mouse event failed for object(ID:%lu)\n",
                  e_handler->base.id);
      return false;
    }
  }
  return true;
}

bool base_handle_keyboard_event(struct events_t *e_handler, SDL_Event *e) {
  if (e_handler->text_event != NULL && !e_handler->text_event(&e_handler->base, e)) {
    SDL_LogWarn(1, "text event failed for object(ID:%lu)\n",
                e_handler->base.id);
    return false;
  }
  return true;
}
