#include "state.h"
#include "SDL3/SDL_init.h"
#include "scene.h"
#include "src/components/font.h"
#include "src/components/win.h"
#include "src/types/color.h"
#include "src/types/scene_types.h"
#include "src/types/state.h"
#include "unicode_str.h"
#include "user_data.h"

bool state_init(struct state_t* s) {
  s->app_state = SDL_APP_CONTINUE;
  s->next_scene = NULL;
  s->current_scene = NULL;
  s->win.background = COLOR_BLACK;
  if (!win_create_main(&s->win, "SGF Example", 640, 480)) {
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
  s->user_data = NULL;
  return true;
}

bool state_switch_scene(struct state_t *s, struct scene_t *scene) {
  s->next_scene = scene;
  return true;
}

void state_free(struct state_t* s) {
  if (s->user_data != NULL) {
    user_data_destroy(&s->user_data);
  }
  state_switch_scene(s, NULL);
  font_free(&s->font);
  win_free(&s->win);
}
