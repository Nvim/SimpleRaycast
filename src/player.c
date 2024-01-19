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

  vec2 position = {WALLSIZE, WALLSIZE};
  vec2 direction = {LEFT, UP};
  player->position = position;
  player->angle = M_PI / 4;
  player->direction = direction;
  player->delta.x = cos(player->angle) * PLAYER_SPEED;
  player->delta.y = sin(player->angle) * PLAYER_SPEED;

  game.player = player;
  return EXIT_SUCCESS;
}

// TODO: peut mieux faire c'est quoi ce cast de golmon
void draw_player() {
  SDL_Rect r;
  r.w = PLAYER_SIZE;
  r.h = PLAYER_SIZE;
  r.x = game.player->position.x;
  r.y = game.player->position.y;

  // vec2 *pos = cast_int(&game.player->position);
  vec2 delta = cast_int(&game.player->delta);
  render_filled_rectangle(&r, &player_colors);
  render_line(&player_colors, &game.player->position, &delta);
  printf("Delta: (%d, %d)\n", delta.x, delta.y);
  printf("Player Delta: (%f, %f)\n", game.player->delta.x,
         game.player->delta.y);
  printf("Player Angle: %f\n", game.player->angle);
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
