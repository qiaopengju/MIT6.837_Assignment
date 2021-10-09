#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vectors.h"

class Camera{
    //generate rays for each screen-space coordinate, described as a Vec2f
public:
    Camera() = default;
    ~Camera() {};

    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;
};

class OrthographicCamera : public Camera{
public:
    //CONSTRUCTOR:
    //The constructor takes as input the center of the image, 
    //the direction vector, an up vector, and the image size
    OrthographicCamera(Vec3f _center, Vec3f _direction, Vec3f _up, float _size);
    ~OrthographicCamera() {}

    //generate rays for each screen-space coordinate
    Ray generateRay(Vec2f point);
    //will be useful when tracing rays through the scene
    float getTMin() const;

private:
    Vec3f center, direction, up, horizontal;
    float size;
};

class PerspectiveCamera : public Camera{
public:
    //CONSTRUCTOR:
    //The constructor takes as input the center of the image, 
    //the direction vector, an up vector, and the image size
    PerspectiveCamera(Vec3f _center, Vec3f _direction, Vec3f _up, float angle_randians);
    ~PerspectiveCamera() {}

    //generate rays for each screen-space coordinate
    Ray generateRay(Vec2f point);
    //will be useful when tracing rays through the scene
    float getTMin() const;

private:
    Vec3f center, direction, up, horizontal;
    float angle_randians;
};
#endif