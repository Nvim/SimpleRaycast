#include "../include/globals.h"
#include "../include/render.h"
#include <SDL2/SDL_rect.h>
#include <math.h>

s_Color player_colors = {255, 255, 0, 255};

u8 init_player() {
  s_Player *player = malloc(sizeof(s_Player));
  ASSERT(player, "Player alloc failed\n");

  vec2 position = {96, 224};
  vec2 direction = {LEFT, UP};
  player->position = position;
  // player->angle = M_PI / 4;
  player->angle = DEG2RAD(60);
  player->direction = direction;
  player->delta.x = cos(player->angle) * PLAYER_SPEED;
  player->delta.y = sin(player->angle) * PLAYER_SPEED;

  game.player = player;
  return EXIT_SUCCESS;
}

void rotate_player(int direction) {
  if (direction == LEFT) {
    game.player->angle -= 0.1;
    if (game.player->angle < 0) {
      game.player->angle += 2 * M_PI;
    }
  } else {
    game.player->angle += 0.1;
    if (game.player->angle > 2 * M_PI) {
      game.player->angle -= 2 * M_PI;
    }
  }
  game.player->delta.x = cos(game.player->angle) * PLAYER_SPEED;
  game.player->delta.y = sin(game.player->angle) * PLAYER_SPEED;
}

// printf("Player Angle: %f\n", game.player->angle);
// printf("Delta: (%d, %d)\n", delta.x, delta.y);
// printf("Player Delta: (%f, %f)\n", game.player->delta.x,
//        game.player->delta.y);
// printf("Player Angle: %f\n", game.player->angle);

//
// printf("Player Angle: %f°\n", player_angle);
// printf("A.x: %d°\n", res.x);
// printf("A.y: %d°\n", res.y);
// printf("Xa: %f°\n", inc.x);
// printf("Ya: %f°\n", inc.y);
// a.x += inc.x;
// a.y += inc.y;
// printf("Lines/Cols: (%d, %d), => ", (int)(a.x / WALLSIZE),
//        (int)(a.y / WALLSIZE));
// printf("Map index: %d, value: %d\n",
//        xyToIndex((int)(a.y / WALLSIZE), (int)(a.x / WALLSIZE)),
//        map[xyToIndex((int)(a.y / WALLSIZE), (int)(a.x / WALLSIZE))]);
