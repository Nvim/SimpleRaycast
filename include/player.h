// PLAYER INIT AND MOVEMENT

#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

extern s_Color player_colors;

u8 init_player();
void rotate_player(int direction);

#endif
