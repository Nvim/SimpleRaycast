
// ALL DRAWING RELATED FUNCTIONS HERE

#ifndef RENDER_H
#define RENDER_H

#include "globals.h"

extern s_Color bgColor;
extern s_Color mapColors;
extern s_Color wallColor_light;
extern s_Color wallColor_dark;

// SDL STUFF:
u8 init_window();
void render_rectangle(SDL_Rect *rect, s_Color *colors);
void render_filled_rectangle(SDL_Rect *rect, s_Color *color);
void render_line(s_Color *colors, vec2 *point1, vec2 *point2);
void window_clear();
void window_display();
void window_cleanUp();

// MINIMAP AND FINAL RENDER:
u8 xyToIndex(int lines, int cols);
void draw_map();
void draw_player();
void render_scene();
void render_scene_1ray();

#endif
