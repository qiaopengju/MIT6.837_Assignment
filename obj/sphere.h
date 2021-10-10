#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.h"
#include "vectors.h"

class Sphere : public Object3D{
public:
    //CONSTRUCTOR
    Sphere(Vec3f _center, float _radius, Material *_material) : 
        center(_center), radius(_radius){ material = _material; }

    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
private:
    Vec3f center;
    float radius;
};
#endif