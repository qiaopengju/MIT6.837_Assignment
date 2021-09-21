#include "sphere.h"

bool Sphere::intersect(const Ray &r, Hit &h, float tmin){
    Vec3f o2c = center - r.getOrigin();     //射线原点指向球心向量
    float tp = o2c.Dot3(r.getDirection());
    float o2c2 = o2c.Dot3(o2c);             //ray, sphere中心距离的平方
    float d2 = o2c2 - tp*tp;
    if (d2 > radius*radius) return false;   //不相交
    float t = sqrt(radius*radius - d2);
    //射线原点在球外部
    if (tp - t < tmin){
        if (tp + t > tmin){ //射线在球内部
            h.set(tp + t, material, r);
            return true;
        } else return false;

    } else {
        h.set(tp - t, material, r);
        return true;
    }
}