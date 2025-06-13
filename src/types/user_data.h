#ifndef SGFC_USER_DATA_TYPES_H
#define SGFC_USER_DATA_TYPES_H

#include <stdatomic.h>
#include "SDL3/SDL_thread.h"
#include "src/types/entries.h"
#include "unicode_str.h"
#include "websocket.h"

enum user_data_status_options {
  UDS_CONNECTING = 0,
  UDS_CONNECTED = 1,
  UDS_ERROR = 2,
  UDS_DISCONNECTED = 3,
};

typedef atomic_int user_data_status;

struct user_data {
  SDL_Thread *thread_parent;
  user_data_status status;
  struct unicode_str_t* data_url;
  struct ws_client_t client;
  struct entry_handler_t entries;
};

#endif
