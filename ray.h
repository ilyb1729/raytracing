#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    point3 orig;
    vec3 dir;
public:
    ray();
    ray(const point3 &orig, const vec3 &dir);

    point3 origin() const;
    vec3 direction() const;

    point3 at(double t) const;
};

#endif
