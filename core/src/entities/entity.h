/**
 * @file entity.h
 * @brief Entity transformation functions.
 */

#ifndef SGF_ENTITY_FUNC_H
#define SGF_ENTITY_FUNC_H

#include <stdbool.h>

struct entity_t;

/**
 * @brief Rotate an entity around the Y-axis (XZ plane rotation).
 *
 * @param[out] ent The entity to rotate.
 * @param[in] angle Rotation angle in radians.
 * @return true on success, false if ent is NULL.
 */
bool entity_rotate_xz(struct entity_t *ent, double angle);

/**
 * @brief Rotate an entity around the X-axis (YZ plane rotation).
 *
 * @param[out] ent The entity to rotate.
 * @param[in] angle Rotation angle in radians.
 * @return true on success, false if ent is NULL.
 */
bool entity_rotate_yz(struct entity_t *ent, double angle);

/**
 * @brief Rotate an entity around the Z-axis (XY plane rotation).
 *
 * @param[out] ent The entity to rotate.
 * @param[in] angle Rotation angle in radians.
 * @return true on success, false if ent is NULL.
 */
bool entity_rotate_xy(struct entity_t *ent, double angle);

#endif
