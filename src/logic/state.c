#include "state.h"
#include "src/types/state.h"

bool state_init(struct state_t* s) {
  return init_render_array(&s->objects, 10);
}

bool state_add_render(struct state_t *s, struct render_interface ri) {
  return insert_render_array(&s->objects, ri);
}

void state_free(struct state_t* s) {
  free_render_array(&s->objects);
}
