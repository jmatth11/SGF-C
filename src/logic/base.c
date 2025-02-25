#include "base.h"
#include <SDL3/SDL_log.h>
#include "src/types/base.h"

bool base_handle_mouse_event(struct events_t *e_handler, SDL_Event *e) {
  SDL_FPoint mouse_pos = {
    .x = e->button.x,
    .y = e->button.y
  };
  if (e_handler->mouse_event) {
    if (e_handler->pointInRect &&
      e_handler->pointInRect(&e_handler->base, mouse_pos)) {
      if (!e_handler->mouse_event(&e_handler->base, e)) {
        SDL_LogWarn(
          1,
          "mouse event failed for object(ID:%lu)\n",
          e_handler->base.id
        );
        return false;
      }
    }
  }
  return true;
}
