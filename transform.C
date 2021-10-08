#include "transform.h"

Transform::Transform(Matrix &m, Object3D *o){
    this->m = m; this->m_inverse = m;
    m_inverse.Inverse();
    m_inverse_transpose = m_inverse;
    m_inverse_transpose.Transpose();
    this->object = o;
}

bool Transform::intersect(const Ray &r, Hit &h, float tmin){
    //transform ray from word space to object space
    Vec3f dir_transform = r.getDirection();
    Vec4f ori_transform(r.getOrigin(), 1.0);
    m_inverse.Transform(dir_transform);
    m_inverse.Transform(ori_transform);
    ori_transform.DivideByW();
    float dir_size = dir_transform.Length();
    dir_transform.Normalize();
    Ray _r(ori_transform.xyz(), dir_transform);
    if (object->intersect(_r, h, tmin)){
        Vec3f word_normal = h.getNormal();
        m_inverse_transpose.Transform(word_normal);
        word_normal.Normalize();
        h.set(h.getT() / dir_size, h.getMaterial(), word_normal, r);
        return true;
    }
    return false;
}