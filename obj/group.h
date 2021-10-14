#ifndef GROUP_H
#define GROUP_H

#include "object3d.h"

class Group : public Object3D{
public:
    //CONSTRUCTOR & DESTRUCTOR
    Group(int _numObjs);
    ~Group();

    int getNumObjects() const { return numObjects; }
    void addObject(int index, Object3D *obj);
    bool intersect(const Ray &r, Hit &h, float tmin);
    bool intersectShadowRay(const Ray &r, Hit &h, float tmin);
    void paint();
    void paintAllBBox();
private:
    Object3D **objList;
    int numObjects;
};
#endif