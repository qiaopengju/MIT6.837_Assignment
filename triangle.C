#include "triangle.h"

Triangle::Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m){
    this->a = a;
    this->b = b;
    this->c = c;
    material = m;
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin){
}