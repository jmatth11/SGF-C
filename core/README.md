# SGF Core Framework Documentation

## Overview

The `core` directory contains the shared framework code for the Simple GUI
Framework (SGF). This is a scene-based application framework built on top of
SDL3 and SDL_ttf, designed to support both native and web platforms.

## Directory Structure

```
core/src/
├── main.c              # Application entry point
├── components/         # UI components
├── entities/           # World entities
├── logic/             # Core framework logic
├── scenes/            # Scene definitions
└── types/             # Type definitions
```

## Architecture

### Application Lifecycle

The framework follows SDL3's callback-based application model defined in `main.c`:

1. **Initialization** (`SDL_AppInit`): Sets up SDL, TTF, window, and initial scene
2. **Event Handling** (`SDL_AppEvent`): Processes SDL events through the current scene
3. **Update/Render Loop** (`SDL_AppIterate`): Updates scene logic and renders children
4. **Cleanup** (`SDL_AppQuit`): Frees resources

### Scene System

Scenes (`logic/scene.c`, `logic/scene.h`) manage:
- **Children**: Renderable objects displayed in priority order
- **Events**: Event listeners for mouse, keyboard, and text input
- **Collisions**: Collision detection objects

Scene lifecycle:
- `load()`: Called when scene becomes active
- `update()`: Called each frame with delta time
- `event()`: Handles SDL events
- `unload()`: Called when scene exits

### Entity/World System

The world system (`logic/world.c`, `logic/world.h`) handles:
- **Coordinate projection**: 3D coordinates (x, y, z) projected to 2D screen space
- **Perspective**: Objects scale based on z-depth
- **Frustum culling**: Objects outside view bounds are not rendered

Entity rotation functions (`entities/entity.c`):
- `entity_rotate_xz()`: Y-axis rotation
- `entity_rotate_yz()`: X-axis rotation
- `entity_rotate_xy()`: Z-axis rotation

## Types (`types/`)

### Core Types

| File | Description |
|------|-------------|
| `base.h` | Base object structures: `base_t`, `render_t`, `events_t`, `collision_event_t`. Defines function pointer types for rendering, collision, and events. |
| `scene_types.h` | Scene definition with load/update/event/unload function pointers |
| `state.h` | Application state container: current scene, window, font, config |
| `win_types.h` | Window structure with SDL window/renderer and background color |
| `world_types.h` | World view configuration: rect, scale, focal length, z-cutoffs |
| `entity.h` | Entity with coordinates, projection, and size. Coordinates use -1..1 range |
| `render_interface.h` | Render attributes (color, blend mode) |

### Component Types

| File | Description |
|------|-------------|
| `button_types.h` | Button with theme, rect, label, and click callback |
| `frame_types.h` | Simple colored rectangle frame |
| `font_types.h` | Font wrapper, label (text display), font manager (planned) |
| `loading_icon.h` | Rotating texture with background |
| `text_input.h` | Text input field with cursor, uses gap buffer |
| `toast_types.h` | Toast notification with type (success/warn/error) and placement |
| `theme_types.h` | Theme colors (currently just color) |

### Utility Types

| File | Description |
|------|-------------|
| `color.h` | Predefined colors: WHITE, BLACK, RED, GREEN, BLUE, YELLOW |
| `math.h` | Math constants: PI, TAU |
| `config_types.h` | Configuration: font file and size |
| `component_type.h` | Generic component base (planned) |
| `character_type.h` | Character entity with health (planned) |

## Components (`components/`)

### Window (`win.c`, `win.h`)
Platform-agnostic window creation and management. Delegates to
platform-specific implementations.

### Button (`button.c`, `button.h`)
- Create with `button_init()`
- Set text with `button_set_text()`
- Get render object with `button_get_render()`
- Supports centered positioning and auto-sizing

### Frame (`frame.c`, `frame.h`)
Simple colored rectangle:
- Create with `frame_init()`
- Set size/color with `frame_set_size()`, `frame_set_color()`
- Get render with `frame_get_render()`

### Label (`font.c`)
Text display component:
- Create with `label_init()`
- Set text with `label_set_text()`
- Position with `label_set_center_pos()` or `label_set_normal_pos()`
- Supports text wrapping with `label_set_wrap_length()`

### Text Input (`text_input.c`, `text_input.h`)
Interactive text field:
- Create with `text_input_init()`
- Get render and event handlers with `text_input_get_render()` and
  `text_input_get_event()`
- Supports cursor movement (left/right keys), deletion, and mouse click
  positioning

### Toast (`toast.c`, `toast.h`)
Notification system:
- Create with `toast_create()`
- Types: SUCCESS, WARN, ERROR
- Placements: 6 positions (corners, edges, center)
- Toast manager (`toast_manager_create()`) handles queuing and display timing

### Loading Icon (`loading_icon.c`, `loading_icon.h`)
Rotating image indicator:
- Create with `loading_icon_init()`
- Update rotation with `loading_icon_update()`
- Render with `loading_icon_get_render()`

## Entities (`entities/`)

### Point (`point.c`, `point.h`)
3D point entity:
- Initialize with `point_init()` using `point_options_t`
- Projects to screen based on world settings
- Supports z-depth scaling

### Entity Functions (`entity.c`, `entity.h`)
Rotation functions for entity coordinates.

## Logic (`logic/`)

### Scene Management (`scene.c`, `scene.h`)
- `scene_create()`: Create new scene
- `scene_add_child()`: Add renderable (sorted by priority)
- `scene_remove_child()`: Remove by ID
- `scene_add_event_listener()`: Add event handler
- `scene_add_collision_listener()`: Add collision object
- `scene_check_events()`: Process SDL events
- `scene_destroy()`: Free scene

### State Management (`state.c`, `state.h`)
- `state_init()`: Initialize window, font, config
- `state_switch_scene()`: Queue scene transition
- `state_free()`: Cleanup resources

### Base Functions (`base.c`, `base.h`)
- `base_generate()`: Create base with unique ID
- `base_id_generate()`: Generate unique IDs
- `base_handle_mouse_event()`: Default mouse event processing
- `base_handle_keyboard_event()`: Default keyboard event processing

### World Functions (`world.c`, `world.h`)
- `world_init_with_rect()`: Initialize with rect bounds
- `world_init_with_win()`: Initialize from window size
- `world_apply()`: Transform rect by world settings
- `world_apply_to_entity()`: Transform entity to screen rect
- `world_should_draw()`: Check if rect is visible
- `world_should_draw_ent()`: Check if entity is visible

### Render Helpers (`render.c`, `render.h`)
- `render_check_args()`: Validate render arguments
- `render_set_blendmode()`: Set blend mode with old mode backup
- `render_transparent_fill_rect()`: Draw transparent rectangle
- `render_get/set_attributes()`: Save/restore render state

### Geometry (`geometry.h`)
- `rectWithinRect()`: Check if two rects overlap (uses SDL3 float rects)

## Scenes (`scenes/`)

### Main Scene (`scenes/main/start.c`, `start.h`)
Example scene demonstrating:
- Point entity creation and rendering
- Entity rotation in update loop
- Basic scene lifecycle

## Usage Example

```c
// Create scene
struct scene_t *scene = scene_create();

// Add a frame
struct frame_t frame;
frame_init(&frame);
frame_set_size(&frame, (SDL_FRect){100, 100, 200, 50});
frame_set_color(&frame, COLOR_BLUE);
scene_add_child(scene, frame_get_render(&frame));

// Add a button
struct button_t button;
button_init(&button, &font);
button_set_text(&button, "Click Me", 8);
button.rect = (SDL_FRect){100, 200, -1, -1}; // auto-size
scene_add_child(scene, button_get_render(&button));

// Switch to scene
state_switch_scene(state, scene);
```

## Rendering Pipeline

1. Clear renderer with background color
2. Call scene's `update()` with delta time
3. Iterate children in priority order
4. Check viewable rect against render viewport
5. Call child's render function with render context
6. Present renderer

Objects are sorted by priority (lower = rendered first). Priority can be set in
the base structure.
