#include "render.h"
#include <stdint.h>

float wave(float x) { 
  return sinf(x * M_PI) * 0.5f + 0.5f; 
}

int main(void) {
  int width = 256;
  int height = 256;
  uint8_t img[height][width][4];
  RenderContext ctx;

  render_init(&ctx, width, height);
  float t = 0;
  do {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        img[y][x][0] = (uint8_t)(x + t * 32) ^ (uint8_t)y;
        img[y][x][1] = (uint8_t)(x + t * 32) ^ (uint8_t)y;
        img[y][x][2] = (uint8_t)(x + t * 32) ^ (uint8_t)y;
      }
    }
    t += 1.0f / 60.0f;
  } while (render_frame(&ctx, (uint8_t *) img));

  render_exit(&ctx);
}
