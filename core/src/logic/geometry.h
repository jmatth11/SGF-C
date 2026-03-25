/**
 * @file geometry.h
 * @brief Geometry helper macros.
 */

#ifndef SGF_GEOMETRY_H
#define SGF_GEOMETRY_H

/**
 * @brief Check if two rectangles overlap (either corner of a is inside b).
 *
 * @param a First rectangle (SDL_FRect).
 * @param b Second rectangle (SDL_FRect).
 * @return Non-zero if rectangles overlap, zero otherwise.
 */
#define rectWithinRect(a, b)                                                   \
  ((((a.x >= b.x) && (a.x <= (b.x + b.w))) &&                                  \
    ((a.y >= b.y) && (a.y <= (b.y + b.h)))) ||                                 \
   ((((a.x + a.w) >= b.x) && (a.x + a.w) <= (b.x + b.w)) &&                    \
    (((a.y + a.h) >= b.y) && (a.y + a.h) <= (b.y + b.h))))

#endif
