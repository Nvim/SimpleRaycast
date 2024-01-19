#ifndef RENDER_H
#define RENDER_H

#include "globals.h"

u8 init_window();
void renderRectangle(SDL_Rect *rect, s_Color color);
void renderFilledRectangle(SDL_Rect *rect, s_Color color);
void renderLine(s_Color colors, vec2 *point1, vec2 *point2);
void window_clear();
void window_display();
void window_cleanUp();

#endif
