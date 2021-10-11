#include <GL/glut.h>
#include "sphere.h"

bool Sphere::intersect(const Ray &r, Hit &h, float tmin){
    //标准化方向向量
    Vec3f dir_nor = r.getDirection();
    float dir_len = dir_nor.Length();
    dir_nor.Normalize();

    Vec3f o2c = center - r.getOrigin();     //射线原点指向球心向量
    //float tp = o2c.Dot3(r.getDirection());
    float tp = o2c.Dot3(dir_nor);
    float o2c2 = o2c.Dot3(o2c);             //ray, sphere中心距离的平方
    float d2 = o2c2 - tp*tp;
    if (d2 > radius*radius) return false;   //不相交
    float t = sqrt(radius*radius - d2);
    //射线原点在球外部
    if ((tp - t)/dir_len < tmin){
        if ((tp + t)/dir_len > tmin){ //射线在球内部
            Vec3f normal = r.pointAtParameter((tp + t)/dir_len) - center;
            normal.Normalize();
            if (h.getMaterial() == NULL || h.getT() > (tp + t)/dir_len) h.set((tp + t)/dir_len, material, normal, r);
            return true;
        } else return false;

    } else if ((tp - t)/dir_len >= tmin){
        Vec3f normal = r.pointAtParameter((tp - t)/dir_len) - center;
        normal.Normalize();
        if (h.getMaterial() == NULL || h.getT() > (tp - t)/dir_len) h.set((tp - t)/dir_len, material, normal, r);
        return true;
    } else return false;
}
