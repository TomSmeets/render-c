#include "render.h"

void render_init(RenderContext *context, int width, int height){
  RenderContext ctx;

  SDL_Init(SDL_INIT_VIDEO);
  ctx.window = SDL_CreateWindow(
      "SDL Window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width, height, 0);

  ctx.renderer = SDL_CreateRenderer(ctx.window, -1, SDL_RENDERER_PRESENTVSYNC);
  ctx.texture = SDL_CreateTexture(ctx.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
  ctx.pitch = width * 4;

  *context = ctx;
}

void render_exit(RenderContext *ctx){
  SDL_DestroyTexture(ctx->texture);
  SDL_DestroyRenderer(ctx->renderer);
  SDL_DestroyWindow(ctx->window);
  SDL_Quit();
}

static int do_events(void){
  SDL_Event ev;
  while(SDL_PollEvent(&ev)){
    switch(ev.type){
      case SDL_QUIT:
        return 0;
    }
  }
  return 1;
}

int render_frame(RenderContext *ctx, ARGB8 *buffer){
  // TODO: optional?
  SDL_RenderClear(ctx->renderer);

  SDL_UpdateTexture(ctx->texture, NULL, buffer, ctx->pitch);
  SDL_RenderCopy(ctx->renderer, ctx->texture, 0, 0);
  SDL_RenderPresent(ctx->renderer);

  return do_events();
}
