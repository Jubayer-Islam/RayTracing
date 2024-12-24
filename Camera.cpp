
#include "Camera.hpp"
#include "Vector3.hpp"

void Camera::setEyePoint(vec3 eyePoint){
    this->_eyePoint = eyePoint;
}
void Camera::setViewDir(vec3 viewDir){
    this->_viewDir = viewDir;
}
void Camera::setUpDir(vec3 upDir){
    this->_upDir = upDir;
}
void Camera::setFoV(double FoV){
    this->_field_of_view = FoV;
}
void Camera::setLookAt(vec3 look_at){
    _viewDir = unit_vector(( look_at - _eyePoint ));
}

const vec3& Camera::getEyePoint() const{
    return _eyePoint;
}
const vec3& Camera::getViewDir() const{
    return _viewDir;
}
const vec3& Camera::getUpDir() const{
    return _upDir;
}
double Camera::getFoV() const{
    return _field_of_view;
}