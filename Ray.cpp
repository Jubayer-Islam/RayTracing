

#include "Ray.hpp"

#include "Intersection.hpp"
#include "Sphere.hpp"

Ray::Ray(vec3 origin, vec3 direction) : _origin(origin), _direction(direction) {}

std::optional<Intersection> Ray::intersects(Sphere& sphere) const {
        //first we get the distance vector from the ray origin to the sphere center
    vec3 dist= sphere._center - this->_origin;  // note: this refers to our ray object we pass in Scene::intersect method, we use ray.intersects(sphere) inside that method

    double d_projection=dot(dist,this->_direction);        // Projection of dist onto the ray's direction
    //measures how far along the ray's direction vector the sphere's center is projected


    if (d_projection < 0) {
        return {};            // The sphere is behind the ray, no intersection  //alt: if (d_projection<0) return std::nullopt;
    }

    //if we are here that means sphere is not behind the ray, continue
   //now we  compute the perpendicular distance from the closest approach to the sphere's centre by using:
    double dist2 = dist.length_squared() - d_projection*d_projection;     //  using Pythagorean theorem:dist2 is Perpendicular distance(between sphere centre & ray's closest approach) squared

    double radius2= sphere._radius * sphere._radius;
    if (dist2>radius2) {
        return {}; //no intersection, the ray misses the sphere
    }

//if we are here, that means sphere radius is big enough to touch the ray
    double d_close = sqrt(radius2 - dist2);  // result after subtracting perpendicular distance from radius
    double t = d_projection - d_close;  // First intersection point
    if (t<0)
    {t= d_projection + d_close;}

    //vec3 intersection_point = this->_origin + this->_direction * t;
    vec3 intersection_point = point_at(t);
    vec3 normal = unit_vector(intersection_point - sphere._center);

    return std::optional<Intersection>(Intersection(sphere._material, normal, t));

}

vec3 Ray::point_at(double t) const {
    return _origin + t * _direction;
}