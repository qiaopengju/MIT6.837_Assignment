#include "grid.h"

Grid::Grid(BoundingBox *bb, int nx, int ny, int nz){
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
    opaque = new bool[nx * ny * nz];
    fill(opaque, opaque + nx*ny*nz, false); //初始都透明
    material = new PhongMaterial(Vec3f(1,1,1), Vec3f(0,0,0), 0);
    //bounding Box
    boundingBox = bb;
    Vec3f max = boundingBox->getMax();
    min = boundingBox->getMin();
    if (nx) lenCellX = (max.x() - min.x()) / nx;
    if (ny) lenCellY = (max.y() - min.y()) / ny;
    if (nz) lenCellZ = (max.z() - min.z()) / nz;
}

Grid::~Grid(){
    delete opaque;
}

bool Grid::intersect(const Ray &r, Hit &h, float tmin){
}

//get cell center pos, index begin from zero
void Grid::getCellPos(Vec3f &pos, const Vec3f &index){
    float x = min.x() + index.x() * lenCellX + lenCellX / 2;
    float y = min.y() + index.y() * lenCellY + lenCellY / 2;
    float z = min.z() + index.z() * lenCellZ + lenCellZ / 2;
    pos = Vec3f(x, y, z);
}

// The paint routine is responsible for
// making the OpenGL calls to draw the object to the screen.
void Grid::paint(void){
    //min max is unit cell size
    Vec3f min = boundingBox->getMin();
    Vec3f max = min + Vec3f(lenCellX, lenCellY, lenCellZ);
    Vec3f v1(min.x(), min.y(), max.z());
    Vec3f v2(max.x(), min.y(), max.z());
    Vec3f v3(max.x(), min.y(), min.z());
    Vec3f v4(min.x(), min.y(), min.z());
    Vec3f v5(min.x(), max.y(), max.z());
    Vec3f v6(max.x(), max.y(), max.z());
    Vec3f v7(max.x(), max.y(), min.z());
    Vec3f v8(min.x(), max.y(), min.z());
    //material->glSetMaterial();
    Vec3f normal;
    material->glSetMaterial();
    glBegin(GL_QUADS);
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (opaque[i*ny*nz + j*nz +k]){
                float sx = i * lenCellX;
                float sy = j * lenCellY;
                float sz = k * lenCellZ;
                //bottom
                Vec3f::Cross3(normal, v1-v2, v3-v2);
                glNormal3f(normal.x(), normal.y(), normal.z());
                glVertex3f(v4.x()+sx, v4.y()+sy, v4.z()+sz);
                glVertex3f(v3.x()+sx, v3.y()+sy, v3.z()+sz);
                glVertex3f(v2.x()+sx, v2.y()+sy, v2.z()+sz);
                glVertex3f(v1.x()+sx, v1.y()+sy, v1.z()+sz);
                //top
                Vec3f::Cross3(normal, v5-v6, v7-v6);
                glNormal3f(normal.x(), normal.y(), normal.z());
                glVertex3f(v8.x()+sx, v8.y()+sy, v8.z()+sz);
                glVertex3f(v7.x()+sx, v7.y()+sy, v7.z()+sz);
                glVertex3f(v6.x()+sx, v6.y()+sy, v6.z()+sz);
                glVertex3f(v5.x()+sx, v5.y()+sy, v5.z()+sz);
                //left
                Vec3f::Cross3(normal, v5-v1, v4-v1);
                glNormal3f(normal.x(), normal.y(), normal.z());
                glVertex3f(v5.x()+sx, v5.y()+sy, v5.z()+sz);
                glVertex3f(v8.x()+sx, v8.y()+sy, v8.z()+sz);
                glVertex3f(v4.x()+sx, v4.y()+sy, v4.z()+sz);
                glVertex3f(v1.x()+sx, v1.y()+sy, v1.z()+sz);
                //right
                Vec3f::Cross3(normal, v3-v2, v6-v2);
                glNormal3f(normal.x(), normal.y(), normal.z());
                glVertex3f(v2.x()+sx, v2.y()+sy, v2.z()+sz);
                glVertex3f(v3.x()+sx, v3.y()+sy, v3.z()+sz);
                glVertex3f(v7.x()+sx, v7.y()+sy, v7.z()+sz);
                glVertex3f(v6.x()+sx, v6.y()+sy, v6.z()+sz);
                //front
                Vec3f::Cross3(normal, v2-v1, v5-v1);
                glNormal3f(normal.x(), normal.y(), normal.z());
                glVertex3f(v1.x()+sx, v1.y()+sy, v1.z()+sz);
                glVertex3f(v2.x()+sx, v2.y()+sy, v2.z()+sz);
                glVertex3f(v6.x()+sx, v6.y()+sy, v6.z()+sz);
                glVertex3f(v5.x()+sx, v5.y()+sy, v5.z()+sz);
                //back
                Vec3f::Cross3(normal, v8-v4, v3-v4);
                glNormal3f(normal.x(), normal.y(), normal.z());
                glVertex3f(v4.x()+sx, v4.y()+sy, v4.z()+sz);
                glVertex3f(v8.x()+sx, v8.y()+sy, v8.z()+sz);
                glVertex3f(v7.x()+sx, v7.y()+sy, v7.z()+sz);
                glVertex3f(v3.x()+sx, v3.y()+sy, v3.z()+sz);
                }
            }
        }
    }
    glEnd();
}