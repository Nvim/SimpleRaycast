#include "../include/globals.h"
#include "../include/player.h"
#include "../include/render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <unistd.h>

s_Game game;
const u8 mapLines = 8;
const u8 map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int main(int argc, char *argv[]) {

  ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL_Init failed: %s\n",
         SDL_GetError());

  ASSERT(IMG_Init(IMG_INIT_PNG), "IMG_Init failed: %s\n", SDL_GetError());
  ASSERT(init_window() == EXIT_SUCCESS, "Window Init failed.\n");
  ASSERT(init_player() == EXIT_SUCCESS, "Player Init failed.\n");

  SDL_Event event;
  u8 gameRunning = 1; // game loop

  /*   Game Loop Begin */

  window_clear();
  draw_player();
  draw_map();
  window_display();

  while (gameRunning) {
    while (SDL_PollEvent(&event)) {
      switch (event.key.keysym.sym) {
      case SDL_QUIT:
      case SDLK_ESCAPE:
        gameRunning = 0;
        break;

      case SDLK_z:
        rotate_player(LEFT);
        break;

      default:
        continue;
      }
      window_clear();
      draw_player();
      draw_map();
      window_display();
    }
  }

  window_cleanUp();
  return EXIT_SUCCESS;
}
