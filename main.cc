#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

int main() {
    // image
    const int width = 256;
    const int height = 256;

    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaning: " << j << " " << std::flush;
        for (int i = 0; i < width; ++ i) {
            color pixel{static_cast<double>(i)/(width-1),
                        static_cast<double>(j)/(height-1),
                        0.25};
            write_color(std::cout, pixel);
        }
    }
    std::cerr << std::endl;
}