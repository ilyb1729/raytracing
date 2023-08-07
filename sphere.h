#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "util.h"

class sphere: public hittable {
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
public:
    sphere();
    sphere(point3 cen, double r, shared_ptr<material> m);
    bool hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const override;
};

#endif