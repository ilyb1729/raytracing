#include "vec3.h"

#include "util.h"

vec3::vec3() {}
vec3::vec3(double x, double y, double z): e{std::vector<double>{x,y,z}} {}

double vec3::getx() const { return e[0]; }
double vec3::gety() const { return e[1]; }
double vec3::getz() const { return e[2]; }

vec3 vec3::operator-() const { return vec3{-e[0],-e[1],-e[2]}; }
double vec3::operator[](int i) const { return e[i]; }
double &vec3::operator[](int i) { return e[i]; }

vec3 &vec3::operator+=(const vec3 &v) {
    for (long unsigned int i=0; i<e.size(); i++) {
        e[i] += v[i];
    }
    return *this;
}
vec3 &vec3::operator-=(const vec3 &v) {
    for (long unsigned int i=0; i<e.size(); i++) {
        e[i] -= v[i];
    }
    return *this;
}
vec3 &vec3::operator*=(const vec3 &v) {
    for (long unsigned int i=0; i<e.size(); i++) {
        e[i] *= v[i];
    }
    return *this;
}
vec3 &vec3::operator*=(double d) {
    for (long unsigned int i=0; i<e.size(); i++) {
        e[i] *= d;
    }
    return *this;
}
vec3 &vec3::operator/=(const vec3 &v) {
    for (long unsigned int i=0; i<e.size(); i++) {
        e[i] /= v[i];
    }
    return *this;
}

vec3 vec3::operator+(const vec3 &v) const { return vec3{*this} += v; }
vec3 vec3::operator-(const vec3 &v) const { return vec3{*this} -= v; }
vec3 vec3::operator/(const vec3 &v) const { return vec3{*this} /= v; }
vec3 vec3::operator*(const vec3 &v) const { return vec3{*this} *= v; }

vec3 vec3::operator/(const double d) const { return *this * (1/d); }
vec3 vec3::operator*(const double d) const { return vec3{*this} *= d; }

double vec3::length() const { return std::sqrt(length_sqr()); }
double vec3::length_sqr() const { 
    double ans = 0;
    for (long unsigned int i=0; i<e.size(); ++i) {
        ans += e[i]*e[i];
    }
    return ans;
}
vec3 vec3::unit() const { return vec3{*this} / this->length(); }
double vec3::sum() const {
    double ans = 0;
    for (long unsigned int i=0; i<e.size(); ++i) {
        ans += e[i];
    }
    return ans;
}
bool vec3::nearZero() const {
    const double s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

vec3 vec3::reflect(const vec3 &normal) const {
    return *this - 2*dot(*this, normal)*normal;
}
vec3 vec3::refract(const vec3 &n, double etai_over_etat) const {
    double cos_theta = fmin(dot(-*this, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (*this + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_sqr())) * n;
    return r_out_parallel + r_out_perp;
}

vec3 vec3::random() {
    return vec3{random_double(), random_double(), random_double()};
}
vec3 vec3::random(double min, double max) {
    return vec3{random_double(min, max), random_double(min, max), random_double(min, max)};
}
vec3 vec3::randInSphere() {
    while (true) {
        vec3 p = vec3::random(-1,1);
        if (p.length_sqr() >= 1) continue;
        return p;
    }
}
vec3 vec3::randUnit() {
    return randInSphere().unit();
}
vec3 vec3::randInDisk() {
    while (true) {
        vec3 p = vec3{random_double(-1,1), random_double(-1,1), 0};
        if (p.length_sqr() >= 1) continue;
        return p;
    }
}

std::ostream &operator<<(std::ostream &out, const vec3& v) {
    out << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return out;
}
vec3 operator*(const double d, const vec3 &v) { return v*d; }
double dot(const vec3 &v1, const vec3 &v2) { return (v1*v2).sum(); }
vec3 cross(const vec3 &v1, const vec3 &v2) { // gonna elision here so dont need to reference it
    return vec3{v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]};
}
