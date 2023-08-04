#include "ray.h"

#include "vec3.h"

ray::ray(): orig{point3{}}, dir{vec3{}} {} // why doesnt origin as a keyword work
ray::ray(const point3 &orig, const vec3 &dir)
    : orig{orig}, dir{dir} {} //  why shouldnt this be a copy constructor??

point3 ray::origin() const { return orig; }
vec3 ray::direction() const { return dir; }

point3 &ray::at(double t) const { return orig + t*dir; }