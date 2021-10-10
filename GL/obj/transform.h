#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"
#include "object3d.h"

class Transform : public Object3D{
public:
    Transform(Matrix &m, Object3D *o);
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
private:
    Matrix m, m_inverse, m_inverse_transpose;
    Object3D *object;
};
#endif