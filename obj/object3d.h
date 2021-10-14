#define GL_SILENCE_DEPRECATION

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <GL/glut.h>
#include "ray.h"
#include "hit.h"
#include "material.h"
#include "boundingbox.h"


class Object3D{
public:
    Object3D() = default;
    ~Object3D(){}
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
    // The paint routine is responsible for
    // making the OpenGL calls to draw the object to the screen.
    virtual void paint(void) = 0;

    //ACCESSOR
    BoundingBox* getBoundingBox() const { return boundingBox; }
protected:
    Material *material;
    BoundingBox *boundingBox;
};
#endif