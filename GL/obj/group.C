#include "group.h"

void Group::addObject(int index, Object3D *obj){
    objList[index] = obj;
}

bool Group::intersect(const Ray &r, Hit &h, float tmin){
    bool flag(false);
    for (int i = 0; i < numObjects; i++){
        if (objList[i]->intersect(r, h, tmin)) flag = true;
    }
    //printf("Hit at %f\n", h.getT());
    return flag;
}

bool Group::intersectShadowRay(const Ray &r, Hit &h, float tmin){
    for (int i = 0; i < numObjects; i++){
        if (objList[i]->intersect(r, h, tmin)) return true;
    }
    return false;
}

void Group::paint(){
    for (int i = 0; i < numObjects; i++){
        objList[i]->paint();
    }
}
