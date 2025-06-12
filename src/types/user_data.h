#ifndef SGFC_USER_DATA_TYPES_H
#define SGFC_USER_DATA_TYPES_H

#include "unicode_str.h"
#include "websocket.h"

struct user_data {
  struct unicode_str_t* data_url;
  struct ws_client_t client;
};

#endif
