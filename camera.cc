#include "camera.h"

#include "hittable_list.h"
#include "hittable.h"
#include "material.h"
#include "util.h"
#include "color.h"

#include <thread>
#include <fstream>
#include <sstream>

color camera::ray_color(const ray &r, const hittable &world, int depth) {
    hit_record rec;
    if (depth <= 0) {
        return color{0, 0, 0};
    }
    if (world.hit(r, 0.001, infty, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, --depth);
        }
        return color{0, 0, 0};
    }
    vec3 unitdir = r.direction().unit();
    double t = .5 * (unitdir.gety() + 1);
    return (1.0 - t) * color{1.0, 1.0, 1.0} + t * color{0.5, 0.7, 1.0};
}

void camera::initialize() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = point3(0, 0, 0);

    // viewport dimensions
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_length = viewport_height * (static_cast<double>(image_width) / image_height);

    auto viewport_u = point3(viewport_length, 0, 0);
    auto viewport_v = point3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + .5 * (pixel_delta_u + pixel_delta_v);
}

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperature, double focus_dist) {
    const double theta = degToRad(vfov);
    const double h = tan(theta / 2);
    const double v_height = 2.0 * h;
    const double v_width = aspect_ratio * v_height;

    w = (lookfrom - lookat).unit();
    u = (cross(vup, w)).unit();
    v = cross(w, u);

    orig = lookfrom;
    horiz = focus_dist * v_width * u; // why multiply by this
    vert = focus_dist * v_height * v;
    bl_corner = orig - horiz / 2 - vert / 2 - focus_dist * w;

    lens_radius = aperature / 2;
}

void camera::render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) { // progress bar somewhere?
        for (int k = 0; k < image_width; ++k) {
            color pixel_color{0, 0, 0};
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (k + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(ostr, pixel_color, samples_per_pixel);
        }
    }
}

ray camera::get_ray(double s, double t) const {
    vec3 rd = lens_radius * vec3::randInDisk();
    vec3 offset = u * rd.getx() + v * rd.gety();
    return ray{orig + offset, bl_corner + s * horiz + t * vert - orig - offset};
}
