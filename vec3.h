#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <vector>

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

    vec3 operator+(const vec3 &v) const;
    vec3 operator-(const vec3 &v) const;
    vec3 operator/(const vec3 &v) const;
    vec3 operator*(const vec3 &v) const; 
    
    vec3 operator/(const double d) const;
    vec3 operator*(const double d) const;

    double length() const;
    double length_sqr() const;
    vec3 unit() const;
    double sum() const;
    bool nearZero() const;

    vec3 reflect(const vec3 &normal) const;
    vec3 refract(const vec3 &n, double etai_over_etat) const;

    static vec3 random();
    static vec3 random(double min, double max);
    static vec3 randInSphere(); // this implementation is a lil slow
    static vec3 randUnit();
    static vec3 randInDisk();

    // not sure if this is good practice to friend, but I do not see any cost/abstraction issue
    friend std::ostream &operator<<(std::ostream &out, const vec3& v);
    friend vec3 operator*(const double d, const vec3 &v); // susge
    friend double dot(const vec3 &v1, const vec3 &v2);
    friend vec3 cross(const vec3 &v1, const vec3 &v2);
};

using point3 = vec3;
using color = vec3;

#endif
