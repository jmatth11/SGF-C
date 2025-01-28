#ifndef GENERIC_WIN_H
#define GENERIC_WIN_H

#include <stdbool.h>
#include <sys/cdefs.h>

// forward declare
struct win_t;

bool win_create_main(struct win_t *win, const char *title, int w, int h) __nonnull((1,2));
void win_free(struct win_t* win) __nonnull((1));

#endif
