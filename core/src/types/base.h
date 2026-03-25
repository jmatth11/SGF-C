/**
 * @file base.h
 * @brief Core type definitions and interfaces for the SGF framework.
 *
 * TODO: Consider subscribing specifically for mouse events instead of checking
 *       every character in the event handler.
 */

#ifndef SGF_BASE_H
#define SGF_BASE_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <stdbool.h>
#include <stdint.h>

#include "array_template.h"

/**
 * @brief Unique identifier type for base objects.
 */
typedef uint32_t base_id;

/**
 * @brief Base structure that all framework objects inherit from.
 *
 * Provides common fields used by all objects including parent reference,
 * unique identifier, and rendering priority.
 */
struct base_t {
  /** @brief Pointer to the parent object that owns this base. */
  void *parent;
  /** @brief Unique identifier for this object. */
  base_id id;
  /** @brief Rendering priority. Lower values are rendered first. */
  uint32_t priority;
};

/**
 * @brief Render context passed to render functions.
 *
 * Contains the SDL renderer and optional world reference needed
 * for rendering operations.
 */
struct render_ctx_t {
  /** @brief The SDL renderer to draw with. */
  SDL_Renderer *ren;
  /** @brief The world for a scene, if one exists. Otherwise NULL. */
  struct world_t *world;
};

/**
 * @brief Context for determining if an object is viewable.
 *
 * Used by viewable_rect_fn to calculate the visible rectangle
 * of an object within the world.
 */
struct viewable_ctx_t {
  /** @brief The world context for coordinate transformation. */
  struct world_t *world;
};

/**
 * @brief Render function pointer type.
 *
 * @param obj The base object to render.
 * @param ctx The render context with renderer and world.
 * @return true on success, false on failure.
 */
typedef bool (*render_fn)(struct base_t *obj, struct render_ctx_t *ctx);

/**
 * @brief Collision rectangle function pointer type.
 *
 * @param obj The base object to get collision rect from.
 * @return The collision rectangle in world coordinates.
 */
typedef SDL_Rect (*collision_rect_fn)(struct base_t *obj);

/**
 * @brief Collision check function pointer type.
 *
 * @param obj The base object to check collisions for.
 * @param other Pointer to the other object to check against.
 * @return true if collision detected, false otherwise.
 */
typedef bool (*collision_fn)(struct base_t *obj, void *other);

/**
 * @brief Mouse event handler function pointer type.
 *
 * @param obj The base object receiving the event.
 * @param event The SDL event data.
 * @return true if event was handled, false otherwise.
 */
typedef bool (*mouse_event_fn)(struct base_t *obj, SDL_Event *event);

/**
 * @brief Point-in-rectangle check function pointer type.
 *
 * @param b The base object to check against.
 * @param p The point to test.
 * @return true if point is within the object's bounds, false otherwise.
 */
typedef bool (*point_check_fn)(struct base_t *b, SDL_FPoint p);

/**
 * @brief Rectangle overlap check function pointer type.
 *
 * @param b The base object to check against.
 * @param r The rectangle to test.
 * @return true if rectangle overlaps the object, false otherwise.
 */
typedef bool (*rect_check_fn)(struct base_t *b, SDL_FRect r);

/**
 * @brief Text input event handler function pointer type.
 *
 * @param b The base object receiving the event.
 * @param event The SDL event data.
 * @return true if event was handled, false otherwise.
 */
typedef bool (*text_event_fn)(struct base_t *b, SDL_Event *event);

/**
 * @brief Focus gained event handler function pointer type.
 *
 * @param b The base object receiving the event.
 * @param e The SDL event data.
 * @return true if event was handled, false otherwise.
 */
typedef bool (*focus_event_fn)(struct base_t *b, SDL_Event *e);

/**
 * @brief Focus lost event handler function pointer type.
 *
 * @param b The base object receiving the event.
 * @param e The SDL event data.
 * @return true if event was handled, false otherwise.
 */
typedef bool (*unfocus_event_fn)(struct base_t *b, SDL_Event *e);

/**
 * @brief Viewable rectangle function pointer type.
 *
 * Returns the rectangle that should be tested for visibility culling.
 *
 * @param b The base object to get viewable rect for.
 * @param ctx The viewable context with world information.
 * @return The rectangle in screen coordinates.
 */
typedef SDL_FRect (*viewable_rect_fn)(struct base_t *b,
                                      struct viewable_ctx_t *ctx);

/**
 * @brief Event handling structure for objects that need input.
 *
 * Contains function pointers for all event types an object can respond to.
 */
struct events_t {
  /** @brief Base object data. */
  struct base_t base;
  /** @brief Check if a point is within this object's bounds. */
  point_check_fn pointInRect;
  /** @brief Check if a rectangle overlaps this object's bounds. */
  rect_check_fn rectInRect;
  /** @brief Handle mouse events (click, move, etc). */
  mouse_event_fn mouse_event;
  /** @brief Handle text input events. */
  text_event_fn text_event;
  /** @brief Handle focus gained events. */
  focus_event_fn focus_event;
  /** @brief Handle focus lost events. */
  unfocus_event_fn unfocus_event;
};

/**
 * @brief Collision detection structure.
 *
 * Contains function pointers for collision rectangle calculation
 * and collision detection.
 */
struct collision_event_t {
  /** @brief Base object data. */
  struct base_t base;
  /** @brief Get the collision rectangle for this object. */
  collision_rect_fn collision_rect;
  /** @brief Check collision against another object. */
  collision_fn collision;
};

/**
 * @brief Renderable object structure.
 *
 * All objects that can be rendered must provide a render function
 * and optionally a viewable rect function for culling.
 */
struct render_t {
  /** @brief Base object data. */
  struct base_t base;
  /** @brief Render function to draw this object. */
  render_fn render;
  /** @brief Get the viewable rectangle for visibility culling. NULL if always visible. */
  viewable_rect_fn get_viewable_rect;
};

/**
 * @brief Dynamic array of base objects.
 */
generate_array_template(base_obj, struct base_t)

/**
 * @brief Dynamic array of event handlers.
 */
    generate_array_template(events, struct events_t)

/**
 * @brief Dynamic array of collision handlers.
 */
        generate_array_template(collision, struct collision_event_t)

/**
 * @brief Dynamic array of renderable objects.
 */
            generate_array_template(render, struct render_t)

#endif
