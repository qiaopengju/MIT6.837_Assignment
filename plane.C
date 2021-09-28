#include "plane.h"

Plane::Plane(Vec3f &_noraml, float _d, Material *_m) : normal(_noraml), d(_d){
    material = _m;
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin){
}