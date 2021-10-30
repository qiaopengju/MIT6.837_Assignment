#ifndef SURFACE_H
#define SURFACE_H
#include "spline.h"
#include "curve.h"

class Surface : public Spline{
public:
    Surface(){

    }
};

class SurfaceOfRevolution : public Surface{
public:    
    SurfaceOfRevolution(Curve *c){

    }
};

class BezierPatch : public Surface{
public:
    BezierPatch(){

    }
    void set(int i, Vec3f v){

    }
};
#endif