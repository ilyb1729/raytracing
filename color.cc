#include "color.h"

#include "vec3.h"
#include <iostream>

// maybe turn this into << override
void write_color(std::ostream &out, color pc) {
    out << static_cast<int>(pc.getx()*255.99) << ' ' 
        << static_cast<int>(pc.gety()*255.99) << ' '
        << static_cast<int>(pc.getz()*255.99) << std::endl;
}