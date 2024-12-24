

#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP
#include "Material.hpp"
#include "Vector3.hpp"

struct Intersection {
    Material _material;
    vec3 _normal;
    double _t;
    Intersection( Material& material, vec3 normal, double t);
    const Material& getMaterial() const;
    const vec3& getNormal() const;
    double getT() const;

};

#endif //INTERSECTION_HPP
