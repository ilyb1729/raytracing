#include "sphere.h"

sphere::sphere(): center{point3{}}, radius{0} {}
sphere::sphere(point3 cen, double r): center{point3{cen}}, radius{r} {}

bool sphere::hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    double a = r.direction().length_sqr(); // is this just a norm
    double h_b = dot(oc, r.direction());
    double c = oc.length_sqr() - radius*radius;
    double discrim = h_b*h_b - a*c;
    if (discrim < 0) {
        return false;
    }
    double sqrtd = sqrt(discrim);

    double root = (-h_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-h_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius; // why scale by radius
    rec.set_face_normal(r, outward_normal);

    return true;
}