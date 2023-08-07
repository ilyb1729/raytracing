#include "camera.h"

#include "util.h"

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperature, double focus_dist) {
    const double theta = degToRad(vfov);
    const double h = tan(theta/2);
    const double v_height = 2.0 * h;
    const double v_width = aspect_ratio * v_height;

    w = (lookfrom-lookat).unit();
    u = (cross(vup, w)).unit();
    v = cross(w, u);

    orig = lookfrom;
    horiz = focus_dist * v_width * u; // why multiply by this
    vert = focus_dist * v_height * v;
    bl_corner = orig - horiz/2 - vert/2 - focus_dist*w;

    lens_radius = aperature / 2;
}
ray camera::get_ray(double s, double t) const {
    vec3 rd = lens_radius * vec3::randInDisk();
    vec3 offset = u * rd.getx() + v * rd.gety();
    return ray{orig + offset, bl_corner + s*horiz + t*vert - orig - offset};
}