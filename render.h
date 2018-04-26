#pragma once
#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int pitch;
} RenderContext;

void render_init(RenderContext *, int width, int height);
int  render_frame(RenderContext *, uint8_t *argb8);
void render_exit(RenderContext *);
