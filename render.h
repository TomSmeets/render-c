#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int pitch;
} RenderContext;

typedef union {
  struct {
    uint8_t b, g, r, a;
  };
  uint8_t argb[4];

  struct {
    uint8_t _unused0;
    uint8_t rgb[3];
  };
} ARGB8;

void render_init(RenderContext *, int width, int height);
int  render_frame(RenderContext *, ARGB8 *);
void render_exit(RenderContext *);
