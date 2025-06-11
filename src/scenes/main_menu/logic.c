#include "logic.h"

#include "gap_buffer.h"
#include "src/types/components/text_input.h"
#include "unicode_str.h"
#include "websocket.h"
#include <stddef.h>

bool validate_user_data(struct text_input_t *field, struct user_data *data) {
  const size_t str_len = gap_buffer_get_len(&field->str);
  const code_point_t *str = gap_buffer_get_str(&field->str);
  struct unicode_str_t *u_str = unicode_str_create();
  // TODO pull out and convert field's string
  //unicode_str_set(u_str, const uint8_t *other, size_t len)
  //unicode_str_to_cstr(struct unicode_str_t *str)
  //ws_client_from_str(const char *url, size_t len, struct ws_client_t *client)
  return false;
}
