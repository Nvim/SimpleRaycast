#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_W 1024
#define WINDOW_H 512
#define RENDER_W 512
#define WALLSIZE 64
#define PLAYER_SPEED 5
#define PLAYER_SIZE 20
#define FOV 60
#define DOF 6
#define DEG2RAD(_d) ((_d) * (M_PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / M_PI))
#define ASSERT(_e, ...)                                                        \
  if (!(_e)) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

enum directions { LEFT, RIGHT, UP, DOWN };
extern const int scaled_wallsize;
extern const int dist_to_plane;
extern const int column_w;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} s_Color;

typedef struct {
  i16 x;
  i16 y;
} vec2;

typedef struct {
  i16 x;
  i16 y;
  i16 z;
} vec3;

typedef struct {
  double x;
  double y;
} vec2f;

typedef struct {
  double x;
  double y;
  double z;
} vec3f;

typedef struct {
  vec2 position;
  vec2f delta;
  double angle;
  vec2 direction; // facing direction
} s_Player;

typedef struct {
  vec2f position;
  double angle;
  double length; // length in pixels
  i8 hit_value;  // map value of where the ray hit
  u8 horizontal; // boolean: 1 = horiz, 0 = vert
} s_Ray;

typedef struct {
  s_Player *player;
  SDL_Window *window;
  SDL_Renderer *renderer;
} s_Game;

extern s_Game game;
extern const u8 mapLines;
extern const u8 map[];

#endif
