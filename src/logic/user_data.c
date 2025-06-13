#include "user_data.h"

#include "reader.h"
#include "src/logic/entry.h"
#include "src/types/user_data.h"
#include "unicode_str.h"
#include "websocket.h"
#include <stdatomic.h>
#include <SDL3/SDL_log.h>


static bool user_data_init(struct user_data *ud) {
  atomic_store(&ud->status, UDS_DISCONNECTED);
  ud->data_url = NULL;
  ud->thread_parent = NULL;
  // result is always true
  (void)ws_client_init(&ud->client);
  if (!entry_handler_init(&ud->entries)) {
    return false;
  }
  return true;
}
struct user_data* user_data_create() {
  struct user_data *result = malloc(sizeof(struct user_data));
  if (!user_data_init(result)) {
    free(result);
    return NULL;
  }
  return result;
}
/**
 * Set the status of the user data with an enum user_data_status_options value.
 *
 * @param ud The user data.
 * @param status The status. See enum user_data_status_options.
 */
void user_data_set_status(struct user_data *ud, int status) {
  atomic_store(&ud->status, status);
}
/**
 * Get the status of the user data.
 *
 * @param ud The user data.
 * @return The status. See enum user_data_status_options.
 */
int user_data_get_status(struct user_data *ud) {
  return atomic_load(&ud->status);
}
bool user_data_add_entry(struct user_data *ud, struct entry *entry) {
  return entry_handler_add(&ud->entries, entry);
}
bool user_data_get_all_entries(struct user_data *ud, struct entry_array *out) {
  return entry_handler_remove_all(&ud->entries, out, false);
}

static bool message_handler(struct ws_client_t *client, struct ws_message_t *msg) {
  SDL_Log("received message\n");
  return true;
}

static int background_thread(void* data) {
  struct user_data *local = (struct user_data*)data;
  if (!ws_client_connect(&local->client)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not connect to websocket endpoint\n");
    user_data_set_status(local, UDS_ERROR);
    return 1;
  }
  user_data_set_status(local, UDS_CONNECTED);
  // this function has an internal loop that stays active as long as the connection is active.
  ws_client_on_msg(&local->client, message_handler);
  user_data_set_status(local, UDS_DISCONNECTED);
  return 1;
}

bool user_data_spawn_handler(struct user_data *ud) {
  user_data_set_status(ud, UDS_CONNECTING);
  ud->thread_parent = SDL_CreateThread(background_thread, "websocket", ud);
  if (ud->thread_parent != NULL) {
    user_data_set_status(ud, UDS_ERROR);
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "could not create websocket thread\n");
    return false;
  }
  return true;
}

static void user_data_free(struct user_data *ud) {
  if (ud == NULL) {
    return;
  }
  atomic_store(&ud->status, UDS_DISCONNECTED);
  ws_client_free(&ud->client);
  if (ud->thread_parent != NULL) {
    SDL_DetachThread(ud->thread_parent);
    ud->thread_parent = NULL;
  }
  unicode_str_destroy(&ud->data_url);
  entry_handler_free(&ud->entries);
}

void user_data_destroy(struct user_data **ud) {
  if (ud == NULL) {
    return;
  }
  user_data_free(*ud);
  *ud = NULL;
}
