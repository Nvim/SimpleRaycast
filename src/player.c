#include "../include/globals.h"
#include "../include/render.h"
#include <SDL2/SDL_rect.h>

s_Color player_colors = {255, 255, 0, 255};

vec2 cast_int(vec2f *v) {
  vec2 vint;
  vint.x = round(v->x);
  vint.y = round(v->y);
  return vint;
}

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

// gets 1st initersect for now
vec2f cast_horiz_ray() {
  double player_angle = RAD2DEG(game.player->angle);
  double aTan = tan(game.player->angle);

  vec2f a;   // 1st intersection point with the grid
  vec2f inc; // increment by this to find next intersect

  a.y = (int)(game.player->position.y / WALLSIZE) * WALLSIZE;
  a.x = game.player->position.x + (game.player->position.y - a.y) / aTan;

  inc.x = WALLSIZE / aTan;

  // if looking up
  if (player_angle < 180) {
    inc.y = WALLSIZE;
    a.y -= 1;
  } else {
    inc.y = -WALLSIZE;
    a.y += WALLSIZE;
  }

  vec2 res = {
      (int)(a.x / WALLSIZE),
      (int)(a.y / WALLSIZE),
  };

  // check if the ray is in a wall:
  // if (map[xyToIndex((int)a.y, (int)a.x)] != 0) {
  //   return a;
  // }
  //
  // for (int i = 0; i < DOF; i++) {
  //   a.x += inc.x;
  //   a.y += inc.y;
  //   if (map[xyToIndex((int)a.y, (int)a.x)] != 0) {
  //     return a;
  //   }
  // }

  // printf("Player Angle: %f°\n", player_angle);
  // printf("A.x: %d°\n", res.x);
  // printf("A.y: %d°\n", res.y);
  // printf("Xa: %f°\n", inc.x);
  // printf("Ya: %f°\n", inc.y);
  return a;
}

void draw_player() {
  SDL_Rect r;
  r.w = PLAYER_SIZE;
  r.h = PLAYER_SIZE;
  r.x = game.player->position.x;
  r.y = game.player->position.y;

  // vec2 *pos = cast_int(&game.player->position);
  vec2f A = cast_horiz_ray();
  vec2 Ai = cast_int(&A);
  render_filled_rectangle(&r, &player_colors);
  render_line(&player_colors, &game.player->position, &Ai);
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
  printf("Player Angle: %f\n", game.player->angle);
}

// printf("Delta: (%d, %d)\n", delta.x, delta.y);
// printf("Player Delta: (%f, %f)\n", game.player->delta.x,
//        game.player->delta.y);
// printf("Player Angle: %f\n", game.player->angle);
