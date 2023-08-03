#include <iostream>
#include "vec3.h"

int main() {
    // image
    const int width = 256;
    const int height = 256;

    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height -1; j >= 0; --j) {
        std::cerr << "\rScanlines remaning: " << j << " " << std::flush;
        for (int i = 0; i < width; ++ i) {
            double r = static_cast<double>(i)/(width-1);
            double g = static_cast<double>(j)/(height-1);
            double b = 0.25;

            int ir = static_cast<int>(r*255.99);
            int ig = static_cast<int>(g*255.99);
            int ib = static_cast<int>(b*255.99);

            std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
        }
    }
    std::cerr << std::endl;
}