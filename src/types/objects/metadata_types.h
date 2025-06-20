#ifndef DB_LISTENER_METADATA_H
#define DB_LISTENER_METADATA_H

#include "unicode_str.h"
#include "array_template.h"
#include <stdbool.h>

#define DB_PRIMARY_KEY_STR "PRIMARY_KEY"
#define DB_FOREIGN_KEY_STR "FOREIGN_KEY"

enum metadata_key_t {
  md_key_primary = 0,
  md_key_foreign,
};

struct connection_table_t {
  struct unicode_str_t *table_name;
  struct unicode_str_t *column_name;
};

struct column_info_t {
  struct unicode_str_t *column_name;
  struct connection_table_t connection;
  bool has_connection;
};

generate_array_template(column_info, struct column_info_t)

struct metadata_t {
  enum metadata_key_t type;
  column_info_array columns;
};

struct table_info_t {
  struct unicode_str_t *name;
  struct metadata_t metadatas[2];
};

#endif
