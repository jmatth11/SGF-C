#ifndef SCENE_ONE_START_H
#define SCENE_ONE_START_H

#include "src/types/entities/entity.h"
#include "src/types/entities/point.h"
#include "src/types/entities/world_types.h"
#include <stdbool.h>

struct scene_one_t {
  struct world_t world;
  struct point_t points[8];
  double angle;
  double dz;
};

bool scene_one_init(struct scene_one_t *s);
struct scene_t *scene_one_prepare(struct scene_one_t *s);
void scene_one_free(struct scene_one_t *s);

#endif
