#include "state.h"
#include "SDL3/SDL_init.h"
#include "scene.h"
#include "src/components/font.h"
#include "src/components/win.h"
#include "src/types/scene_types.h"
#include "src/types/state.h"

bool state_init(struct state_t* s) {
  s->app_state = SDL_APP_CONTINUE;
  s->current_scene = NULL;
  s->win.background = (SDL_Color){
    .r = 0x0,
    .g = 0x0,
    .b = 0x0,
    .a = 0xff
  };
  if (!win_create_main(&s->win, "SGF Example", 480, 640)) {
    SDL_LogError(1, "failed to create main window.\n");
    return false;
  }
  // TODO pull this out to parse from an actual config file
  s->config.font_file = "resources/fonts/SourceCodePro-Regular.ttf";
  s->config.font_size = 18;
  if (!font_init(&s->font, s->win.ren, s->config.font_file, s->config.font_size)) {
    SDL_LogError(1, "failed to create font.\n");
    return false;
  }
  return true;
}

bool state_switch_scene(struct state_t *s, struct scene_t *scene) {
  if (s->current_scene != NULL) {
    s->current_scene->unload(s->current_scene, s);
    scene_destroy(&s->current_scene);
  }
  s->current_scene = scene;
  if (s->current_scene != NULL) {
    s->current_scene->load(s->current_scene, s);
  }
  return true;
}

void state_free(struct state_t* s) {
  state_switch_scene(s, NULL);
  font_free(&s->font);
  win_free(&s->win);
}
