#include "win.h"
#include "../types/win_types.h"

#ifdef __EMSCRIPTEN__
#include "../../../platform/web/src/platform.h"
#else
#include "../../../platform/native/src/platform.h"
#endif

bool win_create_main(struct win_t *win, const char *title, int w, int h) {
    platform_ctx_t ctx = {0};
    if (!platform_create_main(&ctx, title, w, h)) {
        return false;
    }
    win->win = ctx.win;
    win->ren = ctx.ren;
    return true;
}

SDL_Rect win_get_size(struct win_t *win) {
    platform_ctx_t ctx = {.win = win->win, .ren = win->ren};
    return platform_get_size(&ctx);
}

void win_free(struct win_t *win) {
    platform_ctx_t ctx = {.win = win->win, .ren = win->ren};
    platform_free(&ctx);
}
