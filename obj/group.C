#include "group.h"

Group::Group(int _numObjs) : numObjects(_numObjs) {
    objList = new Object3D*[numObjects];
    boundingBox = NULL;
}

Group::~Group(){
    if (boundingBox != NULL) delete boundingBox;
}

void Group::addObject(int index, Object3D *obj){
    objList[index] = obj;
    //caculate bounding box
    if (obj->getBoundingBox() != NULL){ //bounding box 不考虑平面
        if (this->boundingBox == NULL){ //第一个物体
            Vec3f max =obj->getBoundingBox()->getMax();
            Vec3f min =obj->getBoundingBox()->getMin();
            boundingBox = new BoundingBox(min, max);
        } else{ //之后加入的物体
            boundingBox->Extend(obj->getBoundingBox());
        }
    }
}

bool Group::intersect(const Ray &r, Hit &h, float tmin){
    bool flag(false);
    for (int i = 0; i < numObjects; i++){
        if (objList[i]->intersect(r, h, tmin)) flag = true;
    }
    //printf("Hit at %f\n", h.getT());
    return flag;
}

void Group::insertIntoGrid(Grid *g, Matrix *m){
    if (g == NULL) return;
    for (int i = 0; i < numObjects; i++)
        objList[i]->insertIntoGrid(g, m);
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

void Group::paintAllBBox(){
    for (int i = 0; i < numObjects; i++){
        if (objList[i]->getBoundingBox() != NULL)
            objList[i]->getBoundingBox()->paint();
    }
}
