#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_H 512
#define WINDOW_W 1024
#define WALLSIZE 64
#define PLAYER_SPEED 5
#define PLAYER_SIZE 5
#define FOV 60
#define DOF 8
#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / PI))

enum directions { LEFT, RIGHT, UP, DOWN };

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
  vec2f position;
  vec2f delta;
  double angle;
  vec2 direction; // facing direction
} s_Player;

typedef struct {
  vec2f position;
  i8 hit_value;  // map value of where the ray hit
  u8 horizontal; // boolean: 1 = horiz, 0 = vert
} s_Ray;

typedef struct {
  s_Player *player;
  SDL_Window *window;
  SDL_Renderer *renderer;
} s_Game;

extern s_Game *game;
extern const u8 mapLines;
extern const u8 map[];

#endif
