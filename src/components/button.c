#include "button.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "src/types/base.h"
#include "src/types/components/button_types.h"
#include <stdbool.h>

bool button_init(struct button_t *button, uint32_t id) {
  button->id = id;
  button->context = button;
  return true;
}

bool button_render(struct base_t *obj, SDL_Renderer *ren) {
  struct button_t *b = (struct button_t*)obj->parent;
  struct theme_t t = b->theme;
  if (!SDL_SetRenderDrawColor(ren, t.color.r, t.color.g, t.color.b, t.color.a)) {
    return false;
  }

  if (b->texture == NULL) {
    b->texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, b->rect.w, b->rect.h);
  }
  if (b->texture == NULL) {
    SDL_LogError(1, "button texture could not be created: %s\n.", SDL_GetError());
    return false;
  }
  //SDL_RenderGeometry(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Vertex *vertices, int num_vertices, const int *indices, int num_indices)
  return SDL_RenderFillRect(ren, &b->rect);
}

struct render_t button_get_render(struct button_t *button) {
  struct render_t result = {0};
  result.base.id = button->id;
  result.base.parent = button;
  result.render = button_render;
  return result;
}

void button_free(struct button_t *button) {
}
