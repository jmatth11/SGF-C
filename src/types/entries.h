#ifndef DB_LISTENER_ENTRIES_TYPE_H
#define DB_LISTENER_ENTRIES_TYPE_H

#include "SDL3/SDL_mutex.h"
#include "array_template.h"
#include "queue.h"

struct entry {
  // TODO implement
};

generate_array_template(entry, struct entry*)

struct entry_handler_t {
  SDL_Mutex *mutex;
  struct simple_queue_t *entries;
};

#endif
