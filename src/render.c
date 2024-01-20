#include "../include/globals.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>

s_Color bgColor = {40, 40, 40, 255};
s_Color map_colors = {200, 200, 200, 255};

u8 init_window() {
  game.window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
  ASSERT(game.window, "Window failed to init: %s\n", SDL_GetError());

  game.renderer = SDL_CreateRenderer(
      game.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  ASSERT(game.renderer, "Renderer failed to init: %s\n", SDL_GetError());

  SDL_SetRenderDrawColor(game.renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  return EXIT_SUCCESS;
}

void render_rectangle(SDL_Rect *rect, s_Color *colors) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawRect(game.renderer, rect) < 0) {
    fprintf(stderr, "Erreur Creation Rectangle: %s", SDL_GetError());
  }
}

void render_filled_rectangle(SDL_Rect *rect, s_Color *colors) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderFillRect(game.renderer, rect) < 0) {
    fprintf(stderr, "Erreur Fill Rectangle: %s", SDL_GetError());
  }
}

void render_line(s_Color *colors, vec2 *point1, vec2 *point2) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawLine(game.renderer, (int)point1->x, (int)point1->y,
                         (int)point2->x, (int)point2->y)) {
    fprintf(stderr, "Erreur Draw Line: %s", SDL_GetError());
  }
}

void window_clear() {
  // SDL_SetRenderDrawColor(game.renderer, bgColor.r, bgColor.g, bgColor.b,
  // 255);
  SDL_SetRenderDrawColor(game.renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  SDL_RenderClear(game.renderer);
}

void window_display() { SDL_RenderPresent(game.renderer); }

void window_cleanUp() {
  SDL_DestroyRenderer(game.renderer);
  SDL_DestroyWindow(game.window);
  printf("Cleanup done\n");
}

u8 xyToIndex(int lines, int cols) { return 8 * lines + cols; }

// TODO: scaling to any resolution
void draw_map() {
  SDL_Rect rect;
  // int scaled_wallsize = (3 * WALLSIZE) / 4;
  int scaled_wallsize = WALLSIZE;
  rect.h = scaled_wallsize;
  rect.w = scaled_wallsize;
  for (int lines = 0; lines < mapLines; lines++) {
    for (int cols = 0; cols < mapLines; cols++) {
      if (map[xyToIndex(lines, cols)] == 1) {
        rect.x = scaled_wallsize * cols;
        rect.y = scaled_wallsize * lines;

        render_rectangle(&rect, &map_colors);
      }
    }
  }
}
