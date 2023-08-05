#include "camera.h"

#include "util.h"

camera::camera() {
    const double aspect_ratio = 16.0/9.0;
    const double v_height = 2.0;
    const double v_width = aspect_ratio * v_height;
    const double focal_length = 1.0;

    orig = point3{0,0,0};
    horiz = vec3{v_width, 0, 0};
    vert = vec3{0, v_height, 0};
    bl_corner = orig - horiz/2 - vert/2 - vec3{0, 0, focal_length};
}
ray camera::get_ray(double u, double v) const {
    return ray{orig, bl_corner + u*horiz + v*vert - orig};
}