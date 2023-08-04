#include "vec3.h"

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

vec3 &vec3::operator+(const vec3 &v) const { return vec3{*this} += v; }
vec3 &vec3::operator-(const vec3 &v) const { return vec3{*this} -= v; }
vec3 &vec3::operator/(const vec3 &v) const { return vec3{*this} /= v; }
vec3 &vec3::operator*(const vec3 &v) const { return vec3{*this} *= v; }

vec3 &vec3::operator/(const double d) const { return vec3{*this} * (1/d); }
vec3 &vec3::operator*(const double d) const { return vec3{*this} *= d; }

double vec3::length() const { return std::sqrt(length_sqr()); }
double vec3::length_sqr() const { 
    double ans = 0;
    for (long unsigned int i=0; i<e.size(); ++i) {
        ans += e[i]*e[i];
    }
    return ans;
}
vec3 &vec3::unit() const { return vec3{*this} / this->length(); }
double vec3::sum() const {
    double ans = 0;
    for (long unsigned int i=0; i<e.size(); ++i) {
        ans += e[i];
    }
    return ans;
}

std::ostream &operator<<(std::ostream &out, const vec3& v) {
    out << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return out;
}
vec3 &operator*(const double d, const vec3 &v) { return vec3{v}*d; }
double dot(const vec3 &v1, const vec3 &v2) { return (v1*v2).sum(); }
vec3 cross(const vec3 &v1, const vec3 &v2) { // gonna elision here so dont need to reference it
    return vec3{v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]};
}
