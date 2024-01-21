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
  double aTan = tan(ray_angle);
  double ray_angle_deg = RAD2DEG(ray_angle);
  s_Ray *ray = malloc(sizeof(s_Ray));
  ray->angle = ray_angle;
  ray->horizontal = 1;

  vec2f a;   // 1st intersection point with the grid
  vec2f inc; // increment by this to find next intersect

  a.y = (int)(game.player->position.y / WALLSIZE) * WALLSIZE;
  inc.x = WALLSIZE / aTan;

  // if looking up
  if (ray_angle_deg < 180 && ray_angle_deg > 0) {
    inc.y = -WALLSIZE;
    a.y -= 1;
  } else {
    inc.y = WALLSIZE;
    inc.x = -inc.x;
    a.y += WALLSIZE;
  }

  a.x = game.player->position.x + (game.player->position.y - a.y) / aTan;
  ray->position = a;
  ray->hit_value = map[xyToIndex((int)(a.y / WALLSIZE), (int)(a.x / WALLSIZE))];

  for (int i = 0; i < DOF; i++) {
    if (map[xyToIndex((int)(ray->position.y / WALLSIZE),
                      (int)(ray->position.x / WALLSIZE))] != 0) {
      ray->length = get_len(ray);
      return ray;
    }
    ray->position.x += inc.x;
    ray->position.y += inc.y;
    ray->hit_value = map[xyToIndex((int)(ray->position.y / WALLSIZE),
                                   (int)(ray->position.x / WALLSIZE))];
  }

  ray->length = get_len(ray);
  return ray;
}

s_Ray *cast_vert_ray(double ray_angle) {
  double aTan = tan(ray_angle);
  double ray_angle_deg = RAD2DEG(ray_angle);
  s_Ray *ray = malloc(sizeof(s_Ray));
  ray->angle = ray_angle;
  ray->horizontal = 0;

  vec2f a;
  vec2f inc;

  inc.y = WALLSIZE * aTan;
  a.x = (int)(game.player->position.x / WALLSIZE) * WALLSIZE;

  if (ray_angle_deg > 90 && ray_angle_deg < 270) { // looking left
    a.x -= 1;
    inc.x = -WALLSIZE;
  } else {
    a.x += WALLSIZE;
    inc.x = WALLSIZE;
    inc.y = -inc.y;
  }

  a.y = game.player->position.y + (game.player->position.x - a.x) * aTan;
  ray->position = a;
  ray->hit_value = map[xyToIndex((int)(a.y / WALLSIZE), (int)(a.x / WALLSIZE))];

  for (int i = 0; i < DOF; i++) {
    if (map[xyToIndex((int)(ray->position.y / WALLSIZE),
                      (int)(ray->position.x / WALLSIZE))] != 0) {
      ray->length = get_len(ray);
      return ray;
    }
    ray->position.x += inc.x;
    ray->position.y += inc.y;
    ray->hit_value = map[xyToIndex((int)(ray->position.y / WALLSIZE),
                                   (int)(ray->position.x / WALLSIZE))];
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
    return hRay;
  }
  return vRay;
}
