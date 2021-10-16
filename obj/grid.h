#ifndef _GRID_H
#define _GRID_H

#include "object3d.h"

class Grid : public Object3D{
public:
    //Constructor & Distructor
    Grid(BoundingBox *bb, int nx, int ny, int nz);
    ~Grid();

    bool intersect(const Ray &r, Hit &h, float tmin);
    void getCellPos(Vec3f &pos, const int &i, const int &j, const int &k){
        Vec3f index(i, j, k);
        getCellPos(pos, index);
    }
    void getCellPos(Vec3f &pos, const Vec3f &index);
    void setCellOpaque(int i, int j, int k) { opaque[i*ny*nz + j*nz +k] = true; }
    int getNx() const { return nx; }
    int getNy() const { return ny; }
    int getNz() const { return nz; }
    Vec3f getCellSize() const { return Vec3f(lenCellX, lenCellY, lenCellZ); }
    // The paint routine is responsible for
    // making the OpenGL calls to draw the object to the screen.
    void paint(void);
private:
    int nx, ny, nz;
    bool *opaque;
    float lenCellX, lenCellY, lenCellZ;
    Vec3f min; //存min方便计算位置
};
#endif