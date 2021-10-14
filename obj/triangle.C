#include <GL/glut.h>
#include "triangle.h"

Triangle::Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m){
    this->a = a;
    this->b = b;
    this->c = c;
    material = m;
    Vec3f::Cross3(normal, b-a, c-b); //normal = ab x bc;
    normal.Normalize();
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin){
    //标准化方向向量
    Vec3f dir_nor = r.getDirection();
    float dir_len = dir_nor.Length();
    dir_nor.Normalize();

    //判断是否与三角形所在平面相交
    float d = b.Dot3(normal);
    if (dir_nor.Dot3(normal) == 0) return false; //光线方向与平面平行
    float t = (d - r.getOrigin().Dot3(normal)) / (dir_nor.Dot3(normal));
    t /= dir_len;
    if (t < 0) return false; //在光线背面
    if (t < tmin) return false;
    Vec3f hit_pos = r.pointAtParameter(t);
    //与射线相交,判断交点是否在三角形内部
    //有问题，浮点计算很难判等，会出现很多在三角形内部的点没有被判到内部的情况
    //Vec3f v1, v2, v3; //通过叉乘符号判断点是否在三角形内部
    //Vec3f::Cross3(v1, a-hit_pos, b-a);
    //Vec3f::Cross3(v2, b-hit_pos, c-b);
    //Vec3f::Cross3(v3, c-hit_pos, a-c);
    //v1.Normalize(); v2.Normalize(); v3.Normalize();
    //if (v1 == v2 && v2 == v3) 则在三角形内部

    //利用重心公式计算是否在三角形内部
    Vec3f v0 = a - c;
    Vec3f v1 = b - c;
    Vec3f v2 = hit_pos - c;
    float dot00 = v0.Dot3(v0);
    float dot01 = v0.Dot3(v1);
    float dot02 = v0.Dot3(v2);
    float dot11 = v1.Dot3(v1);
    float dot12 = v1.Dot3(v2);
    float u = (dot02*dot11 - dot12*dot01) / (dot00*dot11 - dot01*dot01);
    float v = (dot00*dot12 - dot01*dot02) / (dot00*dot11 - dot01*dot01);
    if (u+v >= 1 || u < 0 || u > 1 || v < 0 || v > 1) return false; //在三角形外
    //在三角形内部
    if (h.getMaterial() != NULL && t > h.getT()) return true;
    h.set(t, material, normal, r);
    return true;
}

void Triangle::paint(){
    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
        glVertex3f(c.x(), c.y(), c.z());
    glEnd();
}