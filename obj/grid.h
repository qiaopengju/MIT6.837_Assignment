#ifndef _GRID_H
#define _GRID_H

#include "object3d.h"
#include "marchingInfo.h"
#include "object3dvector.h"

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
    void getCellPosMin(Vec3f &pos, const int &i, const int &j, const int &k);
    void getCellIndex(Vec3f &index, const Vec3f &pos);
    void setCellOpaque(int i, int j, int k, Object3D* obj) { 
        opaque[i*ny*nz + j*nz + k].addObject(obj);
    }
    int getNx() const { return nx; }
    int getNy() const { return ny; }
    int getNz() const { return nz; }
    BoundingBox* getBoundingBox() const { return boundingBox; }
    Vec3f getCellSize() const { return Vec3f(lenCellX, lenCellY, lenCellZ); }
    //computes the marching increments and the information for the first cell traversed by the ray
    void initializeRayMarch(MarchingInfo &mi, const Ray &r, float tmin);
    // The paint routine is responsible for
    // making the OpenGL calls to draw the object to the screen.
    void paint(void);
    void paintCellRayTree(Vec3f index, Material *m);
    void paintCellRayTree(int i, int j, int k, Material *m) { paintCellRayTree(Vec3f(i, j, k), m); }
    void paintFaceRayTree(Face face, Vec3f index, Material *m);
private:
    int nx, ny, nz;
    Object3DVector *opaque;

    float lenCellX, lenCellY, lenCellZ;
    Vec3f min; //存min方便计算位置
    BoundingBox *boundingBox;
};
#endif