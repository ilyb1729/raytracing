#include <iostream>

#include "util.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"


color ray_color(const ray &r, const hittable &world) {
    hit_record rec;
    if(world.hit(r, 0, infty, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
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

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3{0,0,-1}, 0.5));
    world.add(make_shared<sphere>(point3{0,-100.5,-1}, 100));

    // camera
    const double v_height = 2.0;
    const double v_width = aspect_ratio * v_height;
    const double focal_length = 1.0;

    // cant be const maybe?
    const point3 orig = point3{0,0,0};
    const vec3 horiz = vec3{v_width, 0, 0};
    const vec3 vert = vec3{0, v_height, 0};
    const vec3 bl_corner = orig - horiz/2 - vert/2 - vec3{0, 0, focal_length};

    // render
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaning: " << j << " " << std::flush;
        for (int i = 0; i < width; ++ i) {
            double u = static_cast<double>(i)/(width-1);
            double v = static_cast<double>(j)/(height-1);
            ray r{orig, bl_corner + u*horiz + v*vert - orig};
            write_color(std::cout, ray_color(r, world));
        }
    }
    std::cerr << "Done" << std::endl;
}