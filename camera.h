#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "hittable_list.h"
#include "util.h"
#include <iostream>

class camera {
    point3 center;      // camera center
    point3 pixel00_loc; // location of top left pixel
    vec3 pixel_delta_u; // right one pixel in viewport
    vec3 pixel_delta_v; // down one pixel in viewport

    point3 orig;
    point3 bl_corner;
    vec3 horiz;
    vec3 vert;
    vec3 u, v, w;
    double lens_radius;

    color ray_color(const ray &r, const hittable &world, int depth);
    void initialize();

  public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int image_height;
    int samples_per_pixel = 5;
    int max_depth = 40;
    std::ostream &ostr = std::cout;

    void render(const hittable &world);
    ray get_ray(double u, double v) const;

    camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperature, double focus_dist);
};

#endif