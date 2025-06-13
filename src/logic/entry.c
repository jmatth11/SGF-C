#include "entry.h"

#include "SDL3/SDL_mutex.h"
#include "queue.h"
#include "src/types/entries.h"
#include <stddef.h>

bool entry_handler_init(struct entry_handler_t *eh) {
  eh->entries = simple_queue_create();
  if (eh->entries == NULL) {
    return false;
  }
  eh->mutex = SDL_CreateMutex();
  return true;
}

bool entry_handler_add(struct entry_handler_t *eh, struct entry *entry) {
  SDL_LockMutex(eh->mutex);
  bool result = simple_queue_push(eh->entries, entry);
  SDL_UnlockMutex(eh->mutex);
  return result;
}

bool entry_handler_remove_all(struct entry_handler_t *eh,
                              struct entry_array *out,
                              bool blocking) {
  if (blocking) {
    SDL_LockMutex(eh->mutex);
  } else {
    // return true if we can't acquire the lock
    if (!SDL_TryLockMutex(eh->mutex)) {
      return true;
    }
  }
  bool result = true;
  const size_t len = simple_queue_len(eh->entries);
  if (!entry_array_init(out, len)) {
    SDL_UnlockMutex(eh->mutex);
    return false;
  }
  for (size_t i = 0; i < len; ++i) {
    struct entry *tmp = NULL;
    if (!simple_queue_pop(eh->entries, (void**)&tmp)) {
      result = false;
      break;
    }
    if (tmp != NULL) {
      if (!entry_array_insert(out, tmp)) {
        result = false;
        break;
      }
    }
  }
  if (!result) {
    // if failure, push back all objects that were taken off.
    for (size_t i = 0; i < out->len; ++i) {
      // ignore result
      (void)simple_queue_push(eh->entries, out->entry_data[i]);
    }
    entry_array_free(out);
  }
  SDL_UnlockMutex(eh->mutex);
  return result;
}

void entry_handler_free(struct entry_handler_t *eh) {
  if (eh->entries != NULL) {
    // go through and free everything left over
    const size_t len = simple_queue_len(eh->entries);
    for (size_t i = 0; i < len; ++i) {
      void *tmp = NULL;
      simple_queue_pop(eh->entries, &tmp);
      if (tmp != NULL) {
        free(tmp);
      }
    }
    simple_queue_destroy(&eh->entries);
  }
  if (eh->mutex != NULL) {
    SDL_DestroyMutex(eh->mutex);
  }
}
