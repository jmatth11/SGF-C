#include "entity.h"
#include "src/types/entities/entity.h"
#include <math.h>
#include <stdlib.h>

#include <SDL3/SDL_log.h>

// TODO see if this can be generalized (maybe angular velocity
bool entity_rotate_xz(struct entity_t *ent, double angle) {
  if (ent == NULL)
    return false;
  const double c = cos(angle);
  const double s = sin(angle);
  const double x = ent->coord.x;
  const double z = ent->coord.z;
  ent->coord.x = (x * c) - (z * s);
  ent->coord.z = (x * s) + (z * c);
  return true;
}
