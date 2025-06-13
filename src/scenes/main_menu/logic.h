#ifndef DB_LISTENER_LOGIC_H
#define DB_LISTENER_LOGIC_H

#include "defs.h"
#include "src/types/components/text_input.h"
#include "src/types/user_data.h"
#include <stdbool.h>

bool validate_user_data(struct text_input_t *field, struct user_data *data) __nonnull((1, 2));
bool start_web_thread(struct user_data *data) __nonnull((1));

#endif
