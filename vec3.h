#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <vector>

using point3 = vec3;
using color = vec3;

class vec3 {
    std::vector<double> e = std::vector<double>(3, 0);
public:
    vec3();
    vec3(double x, double y, double z);

    double getx() const;
    double gety() const;
    double getz() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);

    vec3 &operator+=(const vec3 &v);
    vec3 &operator-=(const vec3 &v);
    vec3 &operator*=(const vec3 &v);
    vec3 &operator*=(const double d);
    vec3 &operator/=(const vec3 &v);

    vec3 &operator+(const vec3 &v) const;
    vec3 &operator-(const vec3 &v) const;
    vec3 &operator/(const vec3 &v) const;
    vec3 &operator*(const vec3 &v) const; 
    
    vec3 &operator/(const double d) const;
    vec3 &operator*(const double d) const;

    double length() const;
    double length_sqr() const;
    vec3 &unit() const;
    double sum() const;

    // not sure if this is good practice to friend, but I do not see any cost/abstraction issue
    friend std::ostream &operator<<(std::ostream &out, const vec3& v);
    friend vec3 &operator*(const double d, const vec3 &v); // susge
    friend double dot(const vec3 &v1, const vec3 &v2);
    friend vec3 cross(const vec3 &v1, const vec3 &v2);
};

#endif
