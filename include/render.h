#ifndef RENDER_H
#define RENDER_H

#include "globals.h"

u8 init_window();
void render_rectangle(SDL_Rect *rect, s_Color color);
void render_filled_rectangle(SDL_Rect *rect, s_Color *color);
void render_line(s_Color *colors, vec2 *point1, vec2 *point2);
void window_clear();
void window_display();
void window_cleanUp();

void draw_map();

#endif
