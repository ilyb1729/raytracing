#include "material.h"

#include "util.h"
#include "hittable.h"

lambertian::lambertian(const color &a): albedo{a} {}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    vec3 dir = rec.normal + vec3::randUnit();
    if (dir.nearZero()) {
        dir = rec.normal;
    }
    scattered = ray(rec.p, dir);
    attenuation = albedo;
    return true;
}

metal::metal(const color &a, double f): albedo{a}, fuzz{f} {}

bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    vec3 reflected = r_in.direction().unit().reflect(rec.normal);
    scattered = ray{rec.p, reflected + fuzz*vec3::randInSphere()};
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(double ir): ir{ir} {}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    attenuation = color{1.0,1.0,1.0};
    double refraction_ratio = rec.front_face ? (1.0/ir) : ir; // why 1 over

    vec3 dir = r_in.direction().unit();
    double cos = fmin(dot(-dir, rec.normal), 1.0);
    double sin = sqrt(1.0 - cos*cos);

    bool cannot_refract = refraction_ratio * sin > 1.0;
    vec3 direction;
    if (cannot_refract || reflectance(cos, refraction_ratio) > random_double()) {
        direction = dir.reflect(rec.normal);
    }
    else {
        direction = dir.refract(rec.normal, refraction_ratio);
    }
    scattered = ray{rec.p, direction};
    return true;
}

double dielectric::reflectance(double cos, double ref_idx) {
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cos), 5);
}
