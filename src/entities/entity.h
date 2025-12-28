#ifndef SGF_ENTITY_FUNC_H
#define SGF_ENTITY_FUNC_H

#include <stdbool.h>

struct entity_t;

/**
 * Rotate an entity by the given angle on it's Y-axis.
 *
 * @param[out] ent The entity structure.
 * @param[in] angle The angle to rotate in radians.
 * @return True on success, false otherwise.
 */
bool entity_rotate_xz(struct entity_t *ent, double angle);

/**
 * Rotate an entity by the given angle on it's X-axis.
 *
 * @param[out] ent The entity structure.
 * @param[in] angle The angle to rotate in radians.
 * @return True on success, false otherwise.
 */
bool entity_rotate_yz(struct entity_t *ent, double angle);

/**
 * Rotate an entity by the given angle on it's Z-axis.
 *
 * @param[out] ent The entity structure.
 * @param[in] angle The angle to rotate in radians.
 * @return True on success, false otherwise.
 */
bool entity_rotate_xy(struct entity_t *ent, double angle);

#endif
