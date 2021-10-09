#include "plane.h"

Plane::Plane(Vec3f &_noraml, float _d, Material *_m) : normal(_noraml), d(_d){
    material = _m;
    normal.Normalize();
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin){
    //标准化方向向量
    Vec3f dir_nor = r.getDirection();
    float dir_len = dir_nor.Length();
    dir_nor.Normalize();

    if (dir_nor.Dot3(normal) == 0) return false; //光线方向与平面平行
    float t = (d - r.getOrigin().Dot3(normal)) / (dir_nor.Dot3(normal));
    if (t < 0) return false; //在光线背面
    //与射线相交
    if (t/dir_len < tmin) return false;
    if (h.getMaterial() != NULL && h.getT() < t/dir_len) return true;
    h.set(t/dir_len, material, normal, r);
    return true;
}