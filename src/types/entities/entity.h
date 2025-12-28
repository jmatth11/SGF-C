#ifndef SGF_BASE_ENTITY
#define SGF_BASE_ENTITY

#include <SDL3/SDL_rect.h>
#include <stdbool.h>

/**
 * Coordinate structure.
 * Values should be represented from -1..1
 */
struct coordinate_t {
  float x;
  float y;
  float z;
};

/**
 * Zeroed Coordinate.
 */
#define ZERO_COORD (struct coordinate_t){0, 0, 0};

/**
 * Area structure.
 */
struct area_t {
  float w;
  float h;
};

/**
 * Zeroed Area.
 */
#define ZERO_AREA (struct area_t){0, 0};

/**
 * Entity for a world.
 * Includes rect and projection on Z coordinate.
 */
struct entity_t {
  /* The coordinate in space. */
  struct coordinate_t coord;
  /* projection coordinates */
  struct coordinate_t proj;
  /* The size of the entity. */
  struct area_t size;
  /* Flag to adjust size with Z projection or not. */
  bool adjust_size;
};

/**
 * Zeroed Entity.
 */
#define ZERO_ENTITY                                                            \
  (struct entity_t){                                                           \
      .coord = (struct coordinate_t){0, 0, 0},                                 \
      .proj = (struct coordinate_t){0, 0, 0},                                  \
      .size = (struct area_t){0, 0},                                           \
      .adjust_size = false,                                                    \
  };

#endif
