#ifndef _GRID_H
#define _GRID_H

#include "object3d.h"

class Grid : public Object3D{
public:
    //Constructor & Distructor
    Grid(BoundingBox *bb, int nx, int ny, int nz);
    ~Grid();

    bool intersect(const Ray &r, Hit &h, float tmin);
    // The paint routine is responsible for
    // making the OpenGL calls to draw the object to the screen.
    void paint(void);
private:
    int nx, ny, nz;
    bool *opaque;
};
#endif