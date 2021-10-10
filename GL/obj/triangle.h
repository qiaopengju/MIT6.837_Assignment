#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.h"

class Triangle : public Object3D{
public:
    Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m);
    ~Triangle();

    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
private:
    Vec3f a, b, c;
    Vec3f normal;
};
#endif