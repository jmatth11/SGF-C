#ifndef DB_LISTENER_USER_DATA_H
#define DB_LISTENER_USER_DATA_H

#include "defs.h"
#include <stdbool.h>

struct user_data;
struct entry;
struct entry_array;

bool user_data_init(struct user_data *ud) __nonnull((1));
/**
 * Set the status of the user data with an enum user_data_status_options value.
 *
 * @param ud The user data.
 * @param status The status. See enum user_data_status_options.
 */
void user_data_set_status(struct user_data *ud, int status);
/**
 * Get the status of the user data.
 *
 * @param ud The user data.
 * @return The status. See enum user_data_status_options.
 */
int user_data_get_status(struct user_data *ud);
bool user_data_add_entry(struct user_data *ud, struct entry *entry);
bool user_data_get_all_entries(struct user_data *ud, struct entry_array *out);
void user_data_free(struct user_data *ud);

#endif
