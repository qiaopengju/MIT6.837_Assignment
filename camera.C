#include "camera.h"

OrthographicCamera::OrthographicCamera(Vec3f _center, Vec3f _direction, Vec3f _up, float _size) : 
        center(_center), direction(_direction), up(_up), size(_size) {
    direction.Normalize();
    //right hand
    Vec3f::Cross3(horizontal, direction, up);
    Vec3f::Cross3(up, horizontal, direction);
    horizontal.Normalize();
    up.Normalize();
    //printf("CAMERA-UP: %.1f %.1f %.1f\t HORIZONTAL: %.1f %.1f %.1f\t DIR: %.1f %.1f %.1f\n", up.x(), up.y(), up.z(), horizontal.x(), horizontal.y(), horizontal.z(), direction.x(), direction.y(), direction.z());
}

Ray OrthographicCamera::generateRay(Vec2f point){
    Vec3f pos = center + (point.x()-0.5) * size * horizontal +
        (point.y()-0.5) * size * up;
    //printf("Generate Ray at:(%.1f, %.1f, %.1f)\n", pos.x(), pos.y(), pos.z());
    return Ray(pos, this->direction);
}

float OrthographicCamera::getTMin() const{
    return -std::numeric_limits<float>::max();
}