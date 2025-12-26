#include "start.h"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include <stdbool.h>

#include "src/components/win.h"
#include "src/entities/entity.h"
#include "src/entities/point.h"
#include "src/logic/scene.h"
#include "src/logic/world.h"
#include "src/types/color.h"
#include "src/types/entities/entity.h"
#include "src/types/entities/math.h"
#include "src/types/scene_types.h"
#include "src/types/state.h"

bool scene_one_init(struct scene_one_t *s) {
  s->angle = 0;
  s->dz = 1;
  return true;
}

static bool load(struct scene_t *scene, struct state_t *state) {
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  if (!world_init_with_win(&local->world, &state->win)) {
    return false;
  }
  struct point_options_t options = (struct point_options_t){
      .coord = (struct coordinate_t){-0.25, -0.25, 0.25},
      .size = (struct area_t){20, 20},
      .proj_z = 0,
      .color = COLOR_GREEN,
  };
  for (int i = 0; i < 8; ++i) {
    struct point_t *p = &local->points[i];
    options.coord.y = -options.coord.y;
    if ((i % 2) == 0) {
      options.coord.x = -options.coord.x;
    }
    if (i == 4) {
      options.coord.z = -options.coord.z;
    }
    if (!point_init(p, &options)) {
      return false;
    }
    if (!scene_add_child(scene, point_get_render(p))) {
      return false;
    }
  }
  return true;
}

static bool unload(struct scene_t *scene, struct state_t *state) {
  (void)state;
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  scene_one_free(local);
  free(local);
  return true;
}

static bool update(struct scene_t *scene, struct state_t *state,
                   double deltatime) {
  (void)state;
  struct scene_one_t *local = (struct scene_one_t *)scene->__internal;
  const double angle = PI * deltatime;
  for (int i = 0; i < 8; ++i) {
    struct point_t *p = &local->points[i];
    (void)entity_rotate_xz(&p->entity, angle);
    p->entity.proj_z += 1 * deltatime;
  }
  return true;
}

static bool event(struct scene_t *scene, struct state_t *state,
                  SDL_Event *event) {
  (void)event;
  (void)scene;
  (void)state;
  return true;
}

struct scene_t *scene_one_prepare(struct scene_one_t *s) {
  struct scene_t *result = scene_create();
  result->__internal = s;
  result->load = load;
  result->unload = unload;
  result->update = update;
  result->event = event;
  result->world = &s->world;
  return result;
}

void scene_one_free(struct scene_one_t *s) { (void)s; }
