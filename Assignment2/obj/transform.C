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
    Vec4f dir_transform(r.getDirection(), 0.0); //方向向量w分量为0
    Vec4f ori_transform(r.getOrigin(), 1.0);
    m_inverse.Transform(dir_transform);
    m_inverse.Transform(ori_transform);
    ori_transform.DivideByW();
    Ray _r(ori_transform.xyz(), dir_transform.xyz());
    if (object->intersect(_r, h, tmin)){
        Vec4f word_normal(h.getNormal(), 0.0);
        m_inverse_transpose.Transform(word_normal);
        word_normal.Normalize();
        h.set(h.getT(), h.getMaterial(), word_normal.xyz(), r);
        return true;
    }
    return false;
}