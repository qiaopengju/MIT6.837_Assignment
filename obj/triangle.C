#include <GL/glut.h>
#include "triangle.h"
#include "grid.h"
#include "matrix.h"
#include "raytracing_stats.h"

Triangle::Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m){
    this->a = a;
    this->b = b;
    this->c = c;
    material = m;
    Vec3f::Cross3(normal, b-a, c-b); //normal = ab x bc;
    normal.Normalize();
    //caculate bounding box
    float max_x = max(max(this->a.x(), this->b.x()), this->c.x());
    float max_y = max(max(this->a.y(), this->b.y()), this->c.y());
    float max_z = max(max(this->a.z(), this->b.z()), this->c.z());
    float min_x = min(min(this->a.x(), this->b.x()), this->c.x());
    float min_y = min(min(this->a.y(), this->b.y()), this->c.y());
    float min_z = min(min(this->a.z(), this->b.z()), this->c.z());
    boundingBox = new BoundingBox(Vec3f(min_x, min_y, min_z), Vec3f(max_x, max_y, max_z));
}

Triangle::~Triangle(){
    delete boundingBox;
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin){
    RayTracingStats::IncrementNumIntersections();

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

//Separating Axis Theorem
void Triangle::insertIntoGrid(Grid *g, Matrix *m){
    //caculate 13 axis
    if (g == NULL) return;
    int nx = g->getNx();
    int ny = g->getNy();
    int nz = g->getNz();
    Vec3f cellPos;
    Vec3f halfCellSize = g->getCellSize(); halfCellSize /= 2.f;
    //transform
    Vec3f aT(a), bT(b), cT(c), norT(normal);
    if (m){
        m->Transform(aT);
        m->Transform(bT);
        m->Transform(cT);
        m->TransformDirection(norT); norT.Normalize();
    }
    //caculate axis
    Vec3f f0 = bT - aT, f1 = cT - bT, f2 = aT - cT;
    Vec3f e0(1, 0, 0), e1(0, 1, 0), e2(0, 0, 1);
    Vec3f a00, a01, a02, a10, a11, a12, a20, a21, a22;
    Vec3f::Cross3(a00, e0, f0); a00.Normalize();
    Vec3f::Cross3(a01, e0, f1); a01.Normalize();
    Vec3f::Cross3(a02, e0, f2); a02.Normalize();
    Vec3f::Cross3(a10, e1, f0); a10.Normalize();
    Vec3f::Cross3(a11, e1, f1); a11.Normalize();
    Vec3f::Cross3(a12, e1, f2); a12.Normalize();
    Vec3f::Cross3(a20, e2, f0); a20.Normalize();
    Vec3f::Cross3(a21, e2, f1); a21.Normalize();
    Vec3f::Cross3(a22, e2, f2); a22.Normalize();
    Vec3f axis[] = {e0, e1, e2, norT,
        a00, a01, a02, a10, a11, a12, a20, a21, a22};
    for (int i = 0; i < nx; i++){
        for (int j  = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                g->getCellPos(cellPos, i, j, k);
                Vec3f v0 = aT - cellPos;
                Vec3f v1 = bT - cellPos;
                Vec3f v2 = cT - cellPos;
                bool flag = true;
                for (int aI = 0; aI < 13; aI++){
                    float p0 = axis[aI].Dot3(v0);
                    float p1 = axis[aI].Dot3(v1);
                    float p2 = axis[aI].Dot3(v2);
                    float r = halfCellSize.x() * abs(axis[aI].x()) +
                        halfCellSize.y() * abs(axis[aI].y()) +
                        halfCellSize.z() * abs(axis[aI].z());
                    if (min2(min2(p0, p1), p2) > r || max2(max2(p0, p1), p2) < -r) { //有一个轴分离了
                        //printf("Sparate Axis %d, P0: %.3f, P1 %.3f, P2: %.3f r:%.3f\n", aI, p0, p1, p2, r);
                        flag = false;
                        break;
                    }
                }
                if (flag) 
                    g->setCellOpaque(i, j, k, this);
            }
        }
    }
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