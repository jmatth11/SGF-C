#ifndef SGF_RENDER_HELPERS_H
#define SGF_RENDER_HELPERS_H

#include <stdbool.h>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_blendmode.h>

#include "defs.h"

/**
 * Set the blend mode for the renderer while also grabbing the old blendmode.
 *
 * @param ren The SDL Renderer.
 * @param mode The blend mode to set.
 * @param old The old blend mode. To ignore this param pass NULL in.
 * @return True for success, otherwise false.
 */
bool render_set_blendmode(SDL_Renderer *ren, SDL_BlendMode mode, SDL_BlendMode *old) __nonnull((1));

#endif
