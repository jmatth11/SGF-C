/**
 * @file loading_icon.h
 * @brief Loading icon component functions.
 */

#ifndef SGF_LOADING_ICON_H
#define SGF_LOADING_ICON_H

#include "SDL3/SDL_render.h"
#include "defs.h"
#include "../types/base.h"
#include <stdbool.h>

struct loading_icon_t;

/**
 * @brief Initialize a loading icon from an image file.
 *
 * @param[out] icon Pointer to loading icon structure to initialize.
 * @param[in] ren SDL renderer for texture.
 * @param[in] img Path to the image file.
 * @return true on success, false on failure.
 */
bool loading_icon_init(struct loading_icon_t *icon, SDL_Renderer *ren,
                       const char *img) __nonnull((1, 2, 3));

/**
 * @brief Render the loading icon.
 *
 * @param[in] obj Base object wrapper.
 * @param[in] ren SDL renderer.
 * @return true on success, false on failure.
 */
bool loading_icon_render(struct base_t *obj, SDL_Renderer *ren);

/**
 * @brief Update the icon rotation angle.
 *
 * @param[out] icon Pointer to the loading icon.
 */
void loading_icon_update(struct loading_icon_t *icon);

/**
 * @brief Get the render interface for this loading icon.
 *
 * @param[in] icon Pointer to the loading icon.
 * @return render_t structure with render functions.
 */
struct render_t loading_icon_get_render(struct loading_icon_t *icon);

/**
 * @brief Free loading icon resources.
 *
 * @param[out] icon Pointer to the loading icon to free.
 */
void loading_icon_free(struct loading_icon_t *icon);

#endif
