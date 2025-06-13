#include "logic.h"

#include "SDL3/SDL_log.h"
#include "gap_buffer.h"
#include "src/logic/user_data.h"
#include "src/types/components/text_input.h"
#include "src/types/user_data.h"
#include "unicode_str.h"
#include "websocket.h"
#include "magic.h"
#include <stddef.h>
#include <SDL3/SDL_thread.h>

static void free_codepoint_str(code_point_t **obj) {
  if (obj == NULL) {
    return;
  }
  if (*obj == NULL) {
    return;
  }
  free(*obj);
  *obj = NULL;
}

bool validate_user_data(struct text_input_t *field, struct user_data *data) {
  // clear previous data
  if (data->data_url != NULL) {
    unicode_str_destroy(&data->data_url);
    ws_client_free(&data->client);
  }
  const size_t str_len = gap_buffer_get_len(&field->str);
  code_point_t DEFER(free_codepoint_str) *str = gap_buffer_get_str(&field->str);
  struct unicode_str_t *u_str = unicode_str_create();
  if (unicode_str_set_codepoint(u_str, str, str_len) != str_len) {
    unicode_str_destroy(&u_str);
    return false;
  }
  const size_t url_len = unicode_str_byte_len(u_str);
  char AUTO_C *url = unicode_str_to_cstr(u_str);
  bool valid = ws_client_from_str(url, url_len, &data->client);
  if (!valid) {
    unicode_str_destroy(&u_str);
    return false;
  }
  data->data_url = u_str;
  return true;
}

bool start_web_thread(struct user_data *data) {
  return user_data_spawn_handler(data);
}
