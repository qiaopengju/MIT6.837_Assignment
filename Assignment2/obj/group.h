#ifndef GROUP_H
#define GROUP_H

#include "object3d.h"

class Group : public Object3D{
public:
    //CONSTRUCTOR
    Group(int _numObjs) : numObjects(_numObjs) {
        objList = new Object3D*[numObjects];
    }
    //DESTRUCTOR
    ~Group() {}

    void addObject(int index, Object3D *obj);
    bool intersect(const Ray &r, Hit &h, float tmin);
private:
    Object3D **objList;
    int numObjects;
};
#endif