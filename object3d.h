#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "ray.h"
#include "hit.h"
#include "material.h"

class Object3D{
public:
    Object3D() = default;
    ~Object3D(){}
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
protected:
    Material *material;
};
#endif