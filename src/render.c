#include "../include/globals.h"
#include <SDL2/SDL_video.h>

s_Color bgColor = {40, 40, 40, 255};

u8 init_window() {
  game->window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);

  if (game->window == NULL) {
    fprintf(stderr, "Window failed to init. Error: %s", SDL_GetError());
    return EXIT_FAILURE;
  }

  game->renderer = SDL_CreateRenderer(
      game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (game->renderer == NULL) {
    fprintf(stderr, "Renderer failed to init. Error: %s", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_SetRenderDrawColor(game->renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  return EXIT_SUCCESS;
}

void renderRectangle(SDL_Rect *rect, s_Color *colors) {
  SDL_SetRenderDrawColor(game->renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawRect(game->renderer, rect) < 0) {
    fprintf(stderr, "Erreur Creation Rectangle: %s", SDL_GetError());
  }
}

void renderFilledRectangle(SDL_Rect *rect, s_Color *colors) {
  SDL_SetRenderDrawColor(game->renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderFillRect(game->renderer, rect) < 0) {
    fprintf(stderr, "Erreur Fill Rectangle: %s", SDL_GetError());
  }
}

void renderLine(s_Color *colors, vec2 *point1, vec2 *point2) {
  SDL_SetRenderDrawColor(game->renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawLine(game->renderer, point1->x, point1->y, point2->x,
                         point2->y)) {
    fprintf(stderr, "Erreur Draw Line: %s", SDL_GetError());
  }
}

void window_clear() {
  SDL_SetRenderDrawColor(game->renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  SDL_RenderClear(game->renderer);
}

void window_display() { SDL_RenderPresent(game->renderer); }

void window_cleanUp() {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  printf("Cleanup done\n");
}
