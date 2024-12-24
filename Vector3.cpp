

using namespace std;
#include "Vector3.hpp"
#include <optional>

vec3::vec3() {
    _elements [0] = 0.0;
    _elements [1] = 0.0;
    _elements [2] = 0.0;
}

vec3::vec3(double x, double y, double z) {
    _elements[0] = x;
    _elements[1] = y;
    _elements[2] = z;
}

double vec3::x() const {
    return _elements[0];
}

double vec3::y() const {
    return _elements[1];
}
double vec3::z() const {
    return _elements[2];
}

//explanation for reflection and refraction logic: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel.html
vec3 vec3::reflection(const vec3 &normal) const {

   // The surface normal(it's the axis at which the ray is reflected) and incident direction are essential components for computing reflected ray direction

    // we use the formula: " R = I - 2 * (I · N) * N " from the given link above

    vec3 reflectedRayDirection = *this - 2 * dot(*this, normal) * normal; //  *this represents  incident direction (ray._direction), normal represents the intersection->_normal;

    return reflectedRayDirection;
}

std::optional<vec3> vec3::refraction(const vec3 &normal, double IORRatio) const //called in Scene::traceRay
{
    double cosI = dot(*this, normal);
    int sign = (cosI < 0) ? -1 : 1;
    double n = (sign == 1) ? IORRatio : 1.0 / IORRatio;
    double sinT2 = n*n*(1-cosI*cosI);
    if(sinT2 > 1){
        return {};
    }
    vec3 refractedRayDirection = *(this)*n-normal*(n*cosI - sign * sqrt(1 - sinT2));
    return refractedRayDirection;
}

void vec3::clamp(double min, double max) {
    if(_elements[0] < min){
        _elements[0] = min;
    }
    if(_elements[1] < min){
        _elements[1] = min;
    }
    if(_elements[2] < min){
        _elements[2] = min;
    }

    if(_elements[0] > max){
        _elements[0] = max;
    }
    if(_elements[1] > max){
        _elements[1] = max;
    }
    if(_elements[2] > max){
        _elements[2] = max;
    }
}


//returns a vector where each of the elements is flipped from positive to negative and vice versa
vec3 vec3::operator-() const {
    return vec3{-_elements[0], -_elements[1], -_elements[2]};
}

// return the i-th element of the elements vector
double vec3::operator[](int i) const {
    return _elements[i];
}

// return the i-th element of the element
double& vec3::operator[](int i) {
    return _elements[i];
}


vec3& vec3::operator+=(const vec3& v) {
    _elements[0] += v._elements[0];
    _elements[1] += v._elements[1];
    _elements[2] += v._elements[2];
    return *this;
}

vec3& vec3::operator*=(double t) {
    _elements[0] *= t;
    _elements[1] *= t;
    _elements[2] *= t;
    return *this;
}

vec3& vec3::operator/=(double t) {
    return *this *= 1 / t;
}

// Return the length of the vector
double vec3::length() const {
    return std::sqrt(length_squared());
}

// Return the length but squared
double vec3::length_squared() const {
    return _elements[0] * _elements[0] + _elements[1] * _elements[1] + _elements[2] * _elements[2];
}

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v._elements[0] << ' ' << v._elements[1] << ' ' << v._elements[2];
}

vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u._elements[0] + v._elements[0], u._elements[1] + v._elements[1], u._elements[2] + v._elements[2]);
}

vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u._elements[0] - v._elements[0], u._elements[1] - v._elements[1], u._elements[2] - v._elements[2]);
}

vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u._elements[0] * v._elements[0], u._elements[1] * v._elements[1], u._elements[2] * v._elements[2]);
}

// To scale a number with a vector
vec3 operator*(double t, const vec3& v){
    return vec3(t * v._elements[0], t * v._elements[1], t * v._elements[2]);
}

// To scale a vector with a number
vec3 operator*(const vec3& v, double t){
    return t*v;
}

// To divide a vector by a number
vec3 operator/(const vec3& v, double t) {
    return (1/t)*v;
}

// dot product of a vector
double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

// cross product of a vector
vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u[1] * v[2] - u[2] * v[1],u[2] * v[0] - u[0] * v[2],u[0] * v[1] - u[1] * v[0]);
}

// To normalize a vector such that it has a length of 1, we need to divide a vector by its length
vec3 unit_vector(const vec3& v) {
    return v/v.length();
}