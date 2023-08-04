#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
    point3 center;
    double radius;
public:
    sphere();
    sphere(point3 cen, double r);
    bool hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const override;
};

#endif