#ifndef DB_LISTENER_ENTRY_H
#define DB_LISTENER_ENTRY_H

#include "defs.h"
#include <stdbool.h>

// forward declare
struct entry;
struct entry_handler_t;
struct entry_array;

/**
 * Initialize internals.
 * @return True on success, false otherwise.
 */
bool entry_handler_init(struct entry_handler_t *eh) __nonnull((1));
/**
 * Add an entry to the handler.
 *
 * @param eh The entry handler.
 * @param entry The entry to add. Must be an allocated value.
 * @return True on sucess, false otherwise.
 */
bool entry_handler_add(struct entry_handler_t *eh, struct entry *entry)
    __nonnull((1, 2));
/**
 * Remove all entries from the handler into the given entry array structure.
 * This function can be blocking or non-blocking.
 *
 * Note: If non-blocking the function will return True whether it was successful
 * or it was not able to acquire the lock.
 *
 * @param eh The entry handler.
 * @param out The entry array to populate.
 * @param blocking True for a blocking call, false for non-blocking.
 * @return True for success or not able to acquire the lock, false otherwise.
 */
bool entry_handler_remove_all(struct entry_handler_t *eh,
                              struct entry_array *out, bool blocking) __nonnull((1));
/**
 * Free the entry handler's internals.
 */
void entry_handler_free(struct entry_handler_t *eh);

#endif
