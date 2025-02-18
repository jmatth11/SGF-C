#ifndef GENERIC_WIN_H
#define GENERIC_WIN_H

#include <stdbool.h>

// forward declare
struct win_t;

bool win_create_main(struct win_t *win, const char *title, int w, int h);
void win_free(struct win_t* win);

#endif
