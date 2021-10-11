#include <GL/glut.h>
#include "sphere.h"

int Sphere::theta, Sphere::phi;

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

    } else {
        Vec3f normal = r.pointAtParameter((tp - t)/dir_len) - center;
        normal.Normalize();
        if (h.getMaterial() == NULL || h.getT() > (tp - t)/dir_len) h.set((tp - t)/dir_len, material, normal, r);
        return true;
    }
}

void Sphere::gl_set_theta_phi(const int &_theta, const int &_phi){
    theta = _theta;
    phi = _phi;
}

Vec3f Sphere::getPoint(float _theta, float _phi){
    _phi = _phi * M_PI / 180.f;
    _theta = _theta * M_PI / 180.f;
    float x = center.x() + radius * sin(_phi) * cos(_theta);
    float y = center.y() + radius * sin(_phi) * sin(_theta);
    float z = center.z() + radius * cos(_phi);
    return Vec3f(x, y, z);
}

void Sphere::paint(){
    material->glSetMaterial();
    float delta_theta = 360.f / theta;
    float delta_phi = 180.f / phi;

    //从底部开始渲染
    Vec3f x1, x2, x3, x4, quad_normal;
    glBegin(GL_QUADS);
        for (float iPhi = 0; iPhi <= 180; iPhi += delta_phi) {
            for (float iTheta = 0; iTheta <= 360; iTheta += delta_theta){
                x1 = getPoint(iTheta, iPhi);
                x2 = getPoint(iTheta + delta_theta, iPhi);
                x3 = getPoint(iTheta + delta_theta, iPhi + delta_phi);
                x4 = getPoint(iTheta, iPhi + delta_phi);
                Vec3f::Cross3(quad_normal, x2 - x1, x3 - x2);
                    glNormal3f(quad_normal.x(), quad_normal.y(), quad_normal.z());
                    glVertex3f(x1.x(), x1.y(), x1.z());
                    glVertex3f(x2.x(), x2.y(), x2.z());
                    glVertex3f(x3.x(), x3.y(), x3.z());
                    glVertex3f(x4.x(), x4.y(), x4.z());
            }
        }
    glEnd();
}