#include <GL/glut.h>
#include "sphere.h"
#include "grid.h"
#include "raytracer.h"

int Sphere::theta, Sphere::phi;

Sphere::Sphere(Vec3f _center, float _radius, Material *_material) : 
        center(_center), radius(_radius){ 
    material = _material; 
    //caculate bounding box
    Vec3f transRadius(radius, radius, radius);
    boundingBox = new BoundingBox(center - transRadius, center + transRadius);
    boundingBox->Print();
}

Sphere::~Sphere(){
    delete boundingBox;
}

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

void Sphere::insertIntoGrid(Grid *g, Matrix *m){
    if (g == NULL) return;
    int nx = g->getNx();
    int ny = g->getNy();
    int nz = g->getNz();
    Vec3f cellPos;
    Vec3f halfCellSize = g->getCellSize();
    halfCellSize /= 2;
    for (int i = 0; i < nx; i++){
        for (int j  = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                g->getCellPos(cellPos, i, j, k);
                //printf("Index:%d %d %d LEN:%f\n", i, j, k, (cellPos-center).Length());
                Vec3f closeX, closeY, closeZ;
                Vec3f o2center = center - cellPos;
                if (abs(o2center.x()) > halfCellSize.x()){
                    if (o2center.x() < 0) closeX.Set(-halfCellSize.x(), 0, 0);
                    else closeX.Set(halfCellSize.x(), 0, 0);
                } else closeX.Set(o2center.x(), 0, 0);
                if (abs(o2center.y()) > halfCellSize.y()){
                    if (o2center.y() < 0) closeY.Set(0, -halfCellSize.y(), 0);
                    else closeY.Set(0, halfCellSize.y(), 0);
                } else closeY.Set(0, o2center.y(), 0);
                if (abs(o2center.z()) > halfCellSize.z()){
                    if (o2center.z() < 0) closeZ.Set(0, 0, -halfCellSize.z());
                    else closeZ.Set(0, 0, halfCellSize.z());
                } else closeZ.Set(0, 0, o2center.z());
                Vec3f closePos = cellPos + closeX + closeY + closeZ;

                if ((closePos - center).Length() < radius) {
                    g->setCellOpaque(i, j, k, this);
                }
            }
        }
    }
}

void Sphere::gl_set_theta_phi(const int &_theta, const int &_phi){
    theta = _theta;
    phi = _phi;
}

Vec3f Sphere::getPoint(float _theta, float _phi){
    _phi = _phi * M_PI / 180.f;
    _theta = _theta * M_PI / 180.f;
    float x = center.x() + radius * cos(_phi);
    float y = center.y() + radius * sin(_phi) * sin(_theta);
    float z = center.z() + radius * sin(_phi) * cos(_theta);
    return Vec3f(x, y, z);
}

void Sphere::renderVertexGourad(Vec3f v){
    //Vec3f quad_normal = v - center;
    Vec3f quad_normal = center - v; //wrong! but result is right. but why ? ***************************
    quad_normal.Normalize();
    glNormal3f(quad_normal.x(), quad_normal.y(), quad_normal.z());
    glVertex3f(v.x(), v.y(), v.z());
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
                x2 = getPoint(iTheta, iPhi + delta_phi);
                x3 = getPoint(iTheta + delta_theta, iPhi + delta_phi);
                x4 = getPoint(iTheta + delta_theta, iPhi);
                if (!gouraud){
                    Vec3f::Cross3(quad_normal, x2 - x1, x3 - x2);
                    if (quad_normal.Length() == 0) Vec3f::Cross3(quad_normal, x3 - x2, x4 - x3); //?****
                    glNormal3f(quad_normal.x(), quad_normal.y(), quad_normal.z());
                    glVertex3f(x1.x(), x1.y(), x1.z());
                    glVertex3f(x2.x(), x2.y(), x2.z());
                    glVertex3f(x3.x(), x3.y(), x3.z());
                    glVertex3f(x4.x(), x4.y(), x4.z());
                } else{
                    renderVertexGourad(x1);
                    renderVertexGourad(x2);
                    renderVertexGourad(x3);
                    renderVertexGourad(x4);
                }
                //GL
            }
        }
    glEnd();
}