#ifndef DB_LISTENER_ENTRY_H
#define DB_LISTENER_ENTRY_H

#include "defs.h"
#include <stdbool.h>

// forward declare
struct entry;
struct entry_handler_t;
struct entry_array;

bool entry_handler_init(struct entry_handler_t *eh) __nonnull((1));
bool entry_handler_add(struct entry_handler_t *eh, struct entry *entry)
    __nonnull((1, 2));
bool entry_handler_remove_all(struct entry_handler_t *eh,
                              struct entry_array *out) __nonnull((1));
void entry_handler_free(struct entry_handler_t *eh);

#endif
