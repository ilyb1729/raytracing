#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

class camera {
    point3 orig;
    point3 bl_corner;
    vec3 horiz;
    vec3 vert;
public:
    camera();
    ray get_ray(double u, double v) const;
};

#endif