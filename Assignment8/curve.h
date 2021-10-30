#ifndef CURVE_H
#define CURVE_H
#include "spline.h"

class Curve : public Spline{
public:
    Curve(){

    }
};

class BezierCurve : public Curve{
public:
    BezierCurve(int vNum){

    }
    void set(int i, Vec3f v){

    }
};

class BSplineCurve : public Curve{
public:
    BSplineCurve(int vNum){

    }
    void set(int i, Vec3f v){

    }
};
#endif