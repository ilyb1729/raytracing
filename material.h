#ifndef MATERIAL_H
#define MATERIAL_H

#include "util.h"

struct hit_record;

class material {
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

class lambertian: public material {
    color albedo;
public:
    lambertian(const color &a);
    
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

class metal: public material {
    color albedo;
    double fuzz;
public:
    metal(const color &a, double f);

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

class dielectric: public material {
    double ir;

    static double reflectance(double cos, double ref_idx);
public:
    dielectric(double ir);

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

#endif