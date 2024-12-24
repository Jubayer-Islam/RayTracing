

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>
#include <iostream>
#include <optional>

struct vec3 {
public:
    double _elements[3];

    vec3();
    vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);

    vec3& operator*=(double t);

    vec3& operator/=(double t);

    double length() const;

    double length_squared() const;

    vec3 reflection(const vec3& normal) const;
    std::optional<vec3> refraction(const vec3& normal, double IORRatio) const;
    void clamp(double min, double max);
};

std::ostream& operator<<(std::ostream& out, const vec3& v);

vec3 operator+(const vec3& u, const vec3& v);

vec3 operator-(const vec3& u, const vec3& v);

vec3 operator*(const vec3& u, const vec3& v);

vec3 operator*(double t, const vec3& v);

vec3 operator*(const vec3& v, double t);

vec3 operator/(const vec3& v, double t);

double dot(const vec3& u, const vec3& v);

vec3 cross(const vec3& u, const vec3& v);

vec3 unit_vector(const vec3& v);




#endif //VECTOR3_HPP
