#include "../include/globals.h"
#include "../include/player.h"
#include "../include/render.h"
#include <SDL2/SDL.h>

s_Game *game;
const u8 mapLines = 8;
const u8 map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int main(int argc, char *argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL INIT FAILED: %s\n", SDL_GetError());
  }

  if (!(IMG_Init(IMG_INIT_PNG))) {
    fprintf(stderr, "IMG INIT FAILED: %s\n", SDL_GetError());
  }

  s_Game *game = malloc(sizeof(s_Game));
  game->player = malloc(sizeof(s_Player));
  game->renderer = NULL;
  game->window = NULL;
  if (game == NULL) {
    fprintf(stderr, "Game alloc failed\n");
    return EXIT_FAILURE;
  }
  if (init_window() != EXIT_SUCCESS) {
    fprintf(stderr, "Window alloc failed\n");
    return EXIT_FAILURE;
  }

  // SDL_Event event;
  // u8 gameRunning = 1; // game loop
  //
  // while (gameRunning) {
  //   while (SDL_PollEvent(&event)) {
  //     switch (event.key.keysym.sym) {
  //     case SDL_QUIT:
  //     case SDLK_ESCAPE:
  //       gameRunning = 0;
  //       break;
  //
  //     default:
  //       continue;
  //     }
  //     window_clear();
  //     window_display();
  //   }
  // }
  //
  // window_cleanUp();
  SDL_Quit();
  return EXIT_SUCCESS;
}
