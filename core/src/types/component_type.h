/**
 * @file component_type.h
 * @brief Base component type definition.
 *
 * TODO: Implement generic component system.
 */

#ifndef SGF_BASE_COMPONENT_H
#define SGF_BASE_COMPONENT_H

#include <SDL3/SDL_rect.h>

struct component_t;

/**
 * @brief Component get rect function type.
 *
 * @param component The component to get rectangle from.
 * @return The component's rectangle in screen coordinates.
 */
typedef SDL_FRect (*component_get_rect_fn)(struct component_t *);

/**
 * @brief Base component structure for generic UI components.
 */
struct component_t {
  /** @brief Internal data pointer for component-specific data. */
  void *__internal;
  /** @brief Function to get the component's rectangle. */
  component_get_rect_fn get_rect;
};

#endif
