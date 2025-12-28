#include "entity.h"
#include "src/types/entities/entity.h"
#include <math.h>
#include <stdlib.h>

// TODO see if this can be generalized
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

bool entity_rotate_yz(struct entity_t *ent, double angle) {
  if (ent == NULL)
    return false;
  const double c = cos(angle);
  const double s = sin(angle);
  const double y = ent->coord.y;
  const double z = ent->coord.z;
  ent->coord.y = (y * c) - (z * s);
  ent->coord.z = (y * s) + (z * c);
  return true;
}

bool entity_rotate_xy(struct entity_t *ent, double angle) {
  if (ent == NULL)
    return false;
  const double c = cos(angle);
  const double s = sin(angle);
  const double x = ent->coord.x;
  const double y = ent->coord.y;
  ent->coord.x = (x * c) - (y * s);
  ent->coord.y = (x * s) + (y * c);
  return true;
}
