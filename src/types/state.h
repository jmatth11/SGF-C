#ifndef GENERIC_STATE_TYPE_H
#define GENERIC_STATE_TYPE_H

#include <deps/array_template/array_template.h>

#include "render_interface.h"

generate_array_template(render, struct render_interface);

struct state_t {
  render_array objects;
};

#endif
