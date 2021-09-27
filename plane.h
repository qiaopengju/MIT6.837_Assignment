#ifndef PLANE_H
#define PLANE_H

#include "vectors.h"
#include "material.h"
#include "object3d.h"

class Plane : public Object3D{
public:
    Plane(Vec3f &_noraml, float _d, Material *_m);
    bool intersect(const Ray &r, Hit &h, float tmin);
    ~Plane();
private:
    Vec3f normal;
    //d is the offset from the origin, meaning that the plane equation is P.n = d
    float d;
    Material material;
};
#endif