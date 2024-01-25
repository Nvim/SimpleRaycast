#include "../include/globals.h"
#include "../include/render.h"

vec2 cast_int(vec2f *v) {
  vec2 vint;
  vint.x = round(v->x);
  vint.y = round(v->y);
  return vint;
}

// returns the length of a ray
double get_len(s_Ray *ray) {
  double ray_angle_deg = RAD2DEG(ray->angle);
  double playerY = game.player->position.y;
  double playerX = game.player->position.x;
  double lengthY, lengthX;
  double len;

  if (ray_angle_deg < 180) { // if looking up
    lengthY = playerY - ray->position.y;
  } else {
    lengthY = ray->position.y - playerY;
  }

  if (ray_angle_deg < 90 && ray_angle_deg > 270) { // if looking right
    lengthX = ray->position.x - playerX;
  } else {
    lengthX = playerX - ray->position.x;
  }

  // Pythagore:
  len = sqrt((lengthX * lengthX) + (lengthY * lengthY));

  return len;
}

// sets ray's length to the corrected value
void fix_fisheye(s_Ray *ray) {

  if (ray->angle == game.player->angle) {
    return;
  }

  double cosAngle = (game.player->angle - ray->angle);
  if (RAD2DEG(cosAngle) > 360) {
    cosAngle -= DEG2RAD(360);
  }
  ray->length *= cos(cosAngle);
}

s_Ray *cast_horiz_ray(double ray_angle) {
  double aTan = tan(ray_angle), ray_angle_deg = RAD2DEG(ray_angle);
  double playerX = game.player->position.x, playerY = game.player->position.y;
  s_Ray *ray = malloc(sizeof(s_Ray));
  ray->angle = ray_angle;
  ray->horizontal = 1;
  u8 i = 0, tmp = 0;

  vec2f nearest; // 1st intersection point with the grid
  vec2f step;    // increment by this to find next intersect

  nearest.y = (int)(playerY / WALLSIZE) * WALLSIZE;
  step.x = WALLSIZE / aTan;

  // if looking up
  if (ray_angle_deg < 180 && ray_angle_deg > 0) {
    step.y = -WALLSIZE;
    nearest.y -= 1;
    tmp = 1;
  } else {
    step.y = WALLSIZE;
    step.x = -step.x;
    nearest.y += WALLSIZE;
  }
  nearest.x = playerX + (playerY - nearest.y) / aTan;

  ray->position = nearest;
  ray->hit_value =
      map[xyToIndex((int)(nearest.y / WALLSIZE), (int)(nearest.x / WALLSIZE))];

  while (ray->hit_value == 0) {
    ray->position.x += step.x;
    ray->position.y += step.y;
    ray->hit_value = map[xyToIndex((int)(ray->position.y / WALLSIZE),
                                   (int)(ray->position.x / WALLSIZE))];
    i++;
  }

  ray->length = get_len(ray);
  return ray;
}

s_Ray *cast_vert_ray(double ray_angle) {
  double aTan = tan(ray_angle), ray_angle_deg = RAD2DEG(ray_angle);
  double playerX = game.player->position.x, playerY = game.player->position.y;
  s_Ray *ray = malloc(sizeof(s_Ray));
  ray->angle = ray_angle;
  ray->horizontal = 0;
  u8 i = 0, tmp = 0;

  vec2f nearest;
  vec2f step;

  step.y = WALLSIZE * aTan;
  nearest.x = (int)(playerX / WALLSIZE) * WALLSIZE;

  if (ray_angle_deg > 90 && ray_angle_deg < 270) { // looking left
    nearest.x -= 1;
    step.x = -WALLSIZE;
    tmp = 1;
  } else {
    nearest.x += WALLSIZE;
    step.x = WALLSIZE;
    step.y = -step.y;
  }

  nearest.y = playerY + (playerX - nearest.x) * aTan;
  ray->position = nearest;
  ray->hit_value =
      map[xyToIndex((int)(nearest.y / WALLSIZE), (int)(nearest.x / WALLSIZE))];

  while (ray->hit_value == 0 && i < DOF) {
    ray->position.x += step.x;
    ray->position.y += step.y;
    ray->hit_value = map[xyToIndex((int)(ray->position.y / WALLSIZE),
                                   (int)(ray->position.x / WALLSIZE))];
    i++;
  }

  ray->length = get_len(ray);
  return ray;
}

// return ray's coordinates
s_Ray *cast_ray(double ray_angle) {
  s_Ray *hRay = cast_horiz_ray(ray_angle);
  s_Ray *vRay = cast_vert_ray(ray_angle);
  fix_fisheye(hRay);
  fix_fisheye(vRay);
  double hLen = hRay->length;
  double vLen = vRay->length;

  if (fmin(hLen, vLen) == hLen) {
    free(vRay);
    return hRay;
  }
  free(hRay);
  return vRay;
}
