#include <stdint.h>
#include "render.h"

float wave(float x){
  return sinf(x * M_PI) * 0.5f + 0.5f;
}

int main(void) {
  int width  = 256;
  int height = 256;
  ARGB8 img[width*height];
  RenderContext ctx;

  render_init(&ctx, width, height);
  float t = 0;
  do {
    for(int y = 0; y < height; ++y){
      for(int x = 0; x < width; ++x){
        img[y*width + x] = (ARGB8) {
          .a = 255,
          .r = (uint8_t) (x+t*32) ^ (uint8_t) y,
          .g = (uint8_t) (x+t*32) ^ (uint8_t) y,
          .b = (uint8_t) (x+t*32) ^ (uint8_t) y,
        };
      }
    }

    t += 1.0f / 60.0f;
  } while(render_frame(&ctx, img));

  render_exit(&ctx);
}
