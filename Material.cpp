
#include <cmath>
#include "Material.hpp"

#include "Vector3.hpp"

double Material::getExponent() const{
    return _exponent;
}

bool Material::reflects() const{
    return _local < 1.0;
}
bool Material::refracts() const{
    return _local < 1.0 && _index_of_refraction > 0.0;
}
double Material::getLocalReflectivity() const{
    return _local;
}
double Material::getIndexOfRefraction() const{
    return _index_of_refraction;
}
const vec3& Material::getAmbient() const{
    return _ambient;
}
const vec3& Material::getDiffuse() const{
    return _diffuse;
}
const vec3& Material::getSpecular() const{
    return _specular;
}

double Material::getReflectivity(double cosI) const{

    double R0 = 1 - _local; //R0 represents the reflectivity at normal incidence (when the ray hits the surface head-on).

    int sign = (cosI < 0) ? -1 : 1; // Determines the sign of cosI (the cosine of the angle between the ray and the surface normal).
    //If cosI < 0: The ray is exiting the material (negative cosine).
    //If cosI > 0: The ray is entering the material (positive cosine).

    if (_index_of_refraction != 0.0) //If _index_of_refraction is nonzero, the material allows refraction (like glass or water).
    {
        double n = (sign == 1) ? _index_of_refraction : 1.0 / _index_of_refraction; //If the ray is exiting the material, n = 1 / _index_of_refraction (inverse it).
        double R0sqrt = (n - 1) / (n + 1);
        R0 = R0sqrt * R0sqrt; //Calculating Fresnel reflectance ( R0) at normal incidence
        //Fresnel reflectance ( R0) Accounts for differences in light bending and reflection at the boundary
    }

    ////Apply Schlick's approximation. Purpose : Refine the reflectivity calculation based on the angle of incidence.
    //Accounts for the fact that reflectivity increases as the angle of incidence approaches parallel to the surface (grazing angles).
    return R0 + (1 - R0) * pow(1 - sign * cosI, 5);

    /*
   # Purpose of the Function:

    The function computes the reflectivity of a surface based on:

    *The angle of incidence ( cosI).
    *The index of refraction (IOR) of the material (_index_of_refraction).
    *The material's base reflectivity ( _local).

    It uses a combination of Fresnel equations and Schlick's approximation to simulate real-world light reflection accurately,
    which is critical for rendering realistic images.

   # Practical Example:

    For materials like glass :
        Light reflection varies depending on the viewing angle and the material's refractive properties.
        At normal incidence, reflectivity is low. At grazing angles, reflectivity increases.
    For opaque materials :
        The function simplifies to using _local reflectivity since _index_of_refraction would be zero.

     */

}

