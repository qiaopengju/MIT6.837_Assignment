#include <GL/glut.h>
#include "plane.h"

#define MY_INF 1e6

Plane::Plane(Vec3f &_noraml, float _d, Material *_m) : normal(_noraml), d(_d){
    material = _m;
    normal.Normalize();
    // plane should not have bounding box
    boundingBox = NULL; 
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

void Plane::paint(){
    //v:辅助向量; b1b2:在平面上的两个向量; o2plane:原点投影到平面
    Vec3f v, b1, b2, o2plane;
    if (normal == Vec3f(1, 0, 0)) v = Vec3f(0, 1, 0);// normal is parallel to x axis
    else v = Vec3f(1, 0, 0);
    Vec3f::Cross3(b1, v, normal);
    Vec3f::Cross3(b2, normal, b1);
    float t = d / normal.Dot3(normal);
    o2plane = t * normal;

    material->glSetMaterial();
    Vec3f p1, p2, p3, p4;
    p1 = o2plane - MY_INF*b1 - MY_INF*b2;
    p2 = o2plane + MY_INF*b1 - MY_INF*b2;
    p3 = o2plane + MY_INF*b1 + MY_INF*b2;
    p4 = o2plane - MY_INF*b1 + MY_INF*b2;
    glBegin(GL_QUADS);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p2.x(), p2.y(), p2.z());
        glVertex3f(p3.x(), p3.y(), p3.z());
        glVertex3f(p4.x(), p4.y(), p4.z());
    glEnd();
}