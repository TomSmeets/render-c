#include "render.h"

void render_init(RenderContext *context, int width, int height){
  RenderContext ctx = { 0 };

  SDL_Init(SDL_INIT_VIDEO);
  ctx.window = SDL_CreateWindow(
      "SDL Window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width, height, 0);

  ctx.renderer = SDL_CreateRenderer(ctx.window, -1, SDL_RENDERER_PRESENTVSYNC);
  ctx.texture = SDL_CreateTexture(ctx.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
  ctx.pitch = width * 4;

  ctx.input = (RenderInput) { 0 };
  ctx.delta_time = 1.0f / 60.0f;
  ctx.time = 0.0f;

  *context = ctx;
}

void render_exit(RenderContext *ctx){
  SDL_DestroyTexture(ctx->texture);
  SDL_DestroyRenderer(ctx->renderer);
  SDL_DestroyWindow(ctx->window);
  SDL_Quit();
}

static void do_key(RenderInput *input, uint8_t down, uint32_t key){
  switch(key){
    case SDLK_UP:
    case SDLK_w:
      input->move.y = down ?  1.0f : 0.0f;
      break;

    case SDLK_DOWN:
    case SDLK_s:
      input->move.y = down ? -1.0f : 0.0f;
      break;

    case SDLK_RIGHT:
    case SDLK_d:
      input->move.x = down ?  1.0f : 0.0f;
      break;

    case SDLK_LEFT:
    case SDLK_a:
      input->move.x = down ? -1.0f : 0.0f;
      break;

    case SDLK_i:
      input->look.y = down ?  1.0f : 0.0f;
      break;

    case SDLK_k:
      input->look.y = down ? -1.0f : 0.0f;
      break;

    case SDLK_l:
      input->look.x = down ?  1.0f : 0.0f;
      break;

    case SDLK_j:
      input->look.x = down ? -1.0f : 0.0f;
      break;

    default:
      break;
  }
}

int render_frame(RenderContext *ctx, uint8_t *argb8){
  // TODO: optional?
  SDL_RenderClear(ctx->renderer);

  SDL_UpdateTexture(ctx->texture, NULL, argb8, ctx->pitch);
  SDL_RenderCopy(ctx->renderer, ctx->texture, 0, 0);
  SDL_RenderPresent(ctx->renderer);

  // handle events
  SDL_Event ev;
  while(SDL_PollEvent(&ev)){
    switch(ev.type) {
      case SDL_QUIT:
        return 0;
      case SDL_KEYUP:
        do_key(&ctx->input, 0, ev.key.keysym.sym);
        break;
      case SDL_KEYDOWN:
        do_key(&ctx->input, 1, ev.key.keysym.sym);
        break;
      default:
        break;
    }
  }

  return 1;
}
