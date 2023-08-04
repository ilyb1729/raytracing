#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infty = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degToRad(double deg) {
    return deg * pi / 180.0;
}

#include "ray.h"
#include "vec3.h"

#endif