

#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <utility>

#include "Material.hpp"
#include "Vector3.hpp"

struct Sphere {
    double _radius;
    double _radius_squared;
    vec3 _center;
    Material _material;
    Sphere(double radius, vec3 center, Material material): _radius(radius), _center(center), _radius_squared(radius*radius), _material(material) {}
};




#endif //SPHERE_HPP
