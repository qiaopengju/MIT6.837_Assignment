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
    Vec3f ori_transform = r.getOrigin();
    m_inverse.Transform(dir_transform);
    m_inverse.Transform(ori_transform);
    //dir_transform.Normalize();
    Ray _r(ori_transform, dir_transform);
    if (object->intersect(_r, h, tmin)){
        Vec3f word_normal = h.getNormal();
        m_inverse_transpose.Transform(word_normal);
        h.set(h.getT(), h.getMaterial(), word_normal, r);
        return true;
    }
    return false;
}