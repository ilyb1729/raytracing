#include <iostream>

// includes for the parallel
#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <thread>

#include <chrono>

#include "util.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

const double aspect_ratio = 3.0 / 2.0;
const int width = 200;
const int height = static_cast<int>(width / aspect_ratio);
const int samples = 36;
const int depth = 50;

color ray_color(const ray &r, const hittable &world, int depth) {
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

// generate a scene for rendering
hittable_list random_scene() {
    hittable_list world;

    // refactor this to have unique_ptr instead of shared_ptr?
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            double choose_mat = random_double();
            point3 center(a + .9 * random_double(), .2, b + .9 * random_double());

            if ((center - point3(4, .2, 0)).length() > .9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < .8) {
                    // diffuse
                    color albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, .2, sphere_material));
                } else if (choose_mat < .95) {
                    // metal
                    color albedo = color::random(.5, 1);
                    double fuzz = random_double(0, .5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, .2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, .2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

/*
 *  TODO: rewrite this with classes to be OOP nicer
 *        add a progress bar
 */
int main() {
    point3 lookfrom(13, 2, 3); // move camera to parameter
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam = camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    cam.render(random_scene());

    // code for old threading
    // auto start = std::chrono::high_resolution_clock::now();

    // const int num_cores = 1;
    // std::vector<std::unique_ptr<std::thread>> threads;

    // auto world = random_scene();

    // // make threads
    // for (int i = 0; i < num_cores; ++i) {
    //     threads.emplace_back(std::make_unique<std::thread>(gen_img, world, i));
    // }

    // // output all of them to their respective textfile
    // for (int i = 0; i < num_cores; ++i) {
    //     threads[i]->join();
    // }

    // std::cerr << "Done with first stage" << std::endl;

    // // combine pairs
    // int dpth = 0;
    // int num = combine_pairs(num_cores, dpth++);
    // while (num != 1) {
    //     num = combine_pairs(num, dpth++);
    // }

    // std::cerr << "making the final image" << std::endl;
    // std::cerr << dpth << std::endl;

    // std::ofstream of{"image.ppm"};
    // std::ifstream inf{"tmp" + std::to_string(dpth - 1) + "-0"};

    // of << "P3\n" << width << " " << height << "\n255\n"; // might be faster to have the header embedded in
    // std::string s;
    // while (std::getline(inf, s)) {
    //     of << s << std::endl;
    // }

    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cerr << duration.count() << std::endl;
}