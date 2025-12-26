#ifndef SGF_GEOMETRY_H
#define SGF_GEOMETRY_H

#define rectWithinRect(a, b)                                                   \
  ((((a.x >= b.x) && (a.x <= (b.x + b.w))) &&                                  \
    ((a.y >= b.y) && (a.y <= (b.y + b.h)))) ||                                 \
   ((((a.x + a.w) >= b.x) && (a.x + a.w) <= (b.x + b.w)) &&                    \
    (((a.y + a.h) >= b.y) && (a.y + a.h) <= (b.y + b.h))))

#endif
