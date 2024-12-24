

#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "Vector3.hpp"

class Material{
    vec3 _ambient;
    vec3 _diffuse;
    vec3 _specular;
     double _exponent;
     double _local;
     double _index_of_refraction;
public:
    Material( vec3 _ambient, vec3 _diffuse, vec3 _specular, double _exponent):
            _ambient(_ambient), _diffuse(_diffuse),_specular(_specular), _exponent(_exponent), _local(1), _index_of_refraction(0){}
    Material( vec3 _ambient, vec3 _diffuse, vec3 _specular, double _exponent, double _local):
            _ambient(_ambient), _diffuse(_diffuse),_specular(_specular), _exponent(_exponent), _local(_local), _index_of_refraction(0){}
    Material( vec3 _ambient, vec3 _diffuse, vec3 _specular, double _exponent, double _local, double _index_of_refraction):
            _ambient(_ambient), _diffuse(_diffuse),_specular(_specular), _exponent(_exponent), _local(_local), _index_of_refraction(_index_of_refraction){}



    double getExponent() const;
    bool isShadowCaster() const;
    bool reflects() const;
    bool refracts() const;
    double getLocalReflectivity() const;
    double getIndexOfRefraction() const;
    const vec3& getAmbient() const;
    const vec3& getDiffuse() const;
    const vec3& getSpecular() const;
    double getReflectivity(double cosI) const;

};

#endif //MATERIAL_HPP
