#include "../include/globals.h"

u8 init_player() {
  s_Player *player = malloc(sizeof(s_Player));
  if (player == NULL) {
    return EXIT_FAILURE;
  }
  vec2f position = {WALLSIZE, WALLSIZE};
  vec2 direction = {LEFT, UP};
  player->position = position;
  game->player->angle = M_PI / 4;
  player->direction = direction;

  game->player = player;
  return EXIT_SUCCESS;
}

void rotatePlayer(int direction) {
  if (direction == LEFT) {
    game->player->angle -= 0.1;
    if (game->player->angle < 0) {
      game->player->angle += 2 * M_PI;
    }
  } else {
    game->player->angle += 0.1;
    if (game->player->angle > 2 * M_PI) {
      game->player->angle -= 2 * M_PI;
    }
  }
  game->player->delta.x = cos(game->player->angle * M_PI / 180);
  game->player->delta.y = sin(game->player->angle * M_PI / 180);
}
