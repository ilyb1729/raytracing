#include "color.h"

#include "util.h"
#include <iostream>

// maybe turn this into << override
void write_color(std::ostream &out, color pc, int samples) {
    double r = pc.getx();
    double g = pc.gety();
    double b = pc.getz();

    double scale = 1.0 / samples;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' 
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;
}