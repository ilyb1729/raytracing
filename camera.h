#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

class camera {
    point3 orig;
    point3 bl_corner;
    vec3 horiz;
    vec3 vert;
    vec3 u, v, w;
    double lens_radius;
public:
    camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperature, double focus_dist);
    ray get_ray(double u, double v) const;
};

#endif