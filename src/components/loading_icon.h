#ifndef SGF_LOADING_ICON_H
#define SGF_LOADING_ICON_H

#include <stdbool.h>
#include "defs.h"
#include "src/types/base.h"
#include "SDL3/SDL_render.h"

struct loading_icon_t;

bool loading_icon_init(struct loading_icon_t *icon, SDL_Renderer *ren, const char *img) __nonnull((1, 2, 3));
bool loading_icon_render(struct base_t *obj, SDL_Renderer *ren);
void loading_icon_update(struct loading_icon_t *icon);
struct render_t loading_icon_get_render(struct loading_icon_t *icon);
void loading_icon_free(struct loading_icon_t *icon);

#endif
