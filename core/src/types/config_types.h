/**
 * @file config_types.h
 * @brief Configuration type definition.
 */

#ifndef SGF_CONFIG_TYPES_H
#define SGF_CONFIG_TYPES_H

#include <stddef.h>

/**
 * @brief Application configuration structure.
 */
struct config_t {
  /** @brief Path to the font file to use. */
  char *font_file;
  /** @brief Font size in points. */
  size_t font_size;
};

#endif
