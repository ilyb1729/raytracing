#include <iostream>

#include "util.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"


color ray_color(const ray &r, const hittable &world, int depth) {
    hit_record rec;
    if (depth <= 0) {
        return color{0,0,0};
    }
    if(world.hit(r, 0.001, infty, rec)) {
        point3 target = rec.p + rec.normal + vec3::randUnit();
        return 0.5 * ray_color(ray(rec.p, target-rec.p), world, --depth);
    }
    vec3 unitdir = r.direction().unit();
    double t = .5*(unitdir.gety() + 1);
    return (1.0-t)*color{1.0, 1.0, 1.0} + t*color{0.5, 0.7, 1.0};
}

int main() {
    // image
    const double aspect_ratio = 16.0/9.0;
    const int width = 400;
    const int height = static_cast<int>(width/aspect_ratio);
    const int samples = 100;
    const int depth = 50;

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3{0,0,-1}, 0.5));
    world.add(make_shared<sphere>(point3{0,-100.5,-1}, 100));

    // camera
    camera cam;

    // render
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaning: " << j << " " << std::flush;
        for (int i = 0; i < width; ++ i) {
            color pixel_color{0,0,0};
            for (int s = 0; s < samples; ++s) {
                double u = (i+random_double())/(width-1);
                double v = (j+random_double())/(height-1);
                ray r = cam.get_ray(u,v);
                pixel_color += ray_color(r, world, depth);
            }
            write_color(std::cout, pixel_color, samples);
        }
    }
    std::cerr << "Done" << std::endl;
}