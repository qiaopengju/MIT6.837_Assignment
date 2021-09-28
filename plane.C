#include "plane.h"

Plane::Plane(Vec3f &_noraml, float _d, Material *_m) : normal(_noraml), d(_d){
    material = _m;
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin){
    if (r.getDirection().Dot3(normal) == 0) return false; //光线方向与平面平行
    float t = (d - r.getOrigin().Dot3(normal)) / (r.getDirection().Dot3(normal));
    if (t < 0) return false; //在光线背面
    //与射线相交
    if (t < tmin) return false;
    if (h.getMaterial() != NULL && h.getT() < t) return true;
    h.set(t, material, normal, r);
    return true;
}