#include "render.h"
#include <stdint.h>

int main(void) {
  int width = 256;
  int height = 256;
  uint8_t img[height][width][4];
  RenderContext ctx;

  render_init(&ctx, width, height);

  float dx = 0;
  float dy = 0;
  do {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        img[y][x][0] = (uint8_t)(x - dx) ^ (uint8_t)(y + dy);
        img[y][x][1] = (uint8_t)(x - dx) ^ (uint8_t)(y + dy);
        img[y][x][2] = (uint8_t)(x - dx) ^ (uint8_t)(y + dy);
      }
    }

    dx += ctx.input.move.x*ctx.delta_time*256.0f;
    dy += ctx.input.move.y*ctx.delta_time*256.0f;
  } while (render_frame(&ctx, (uint8_t *) img));

  render_exit(&ctx);
}
