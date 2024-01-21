// RAY LOGIC AND HELPER FUNCITONS:

#ifndef RAY_H

#define RAY_H

#include "globals.h"

vec2 cast_int(vec2f *v);
void fix_fisheye(s_Ray *ray);
s_Ray *cast_ray(double ray_angle);

#endif // !RAY_H
