#define GL_SILENCE_DEPRECATION

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <GL/glut.h>
#include "ray.h"
#include "hit.h"
#include "material.h"
#include "boundingbox.h"
#include "object3dvector.h"

class Grid;
class Transform;

class Object3D{
public:
    Object3D() = default;
    virtual ~Object3D();
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
    virtual void insertIntoGrid(Grid *g, Matrix *m);
    // The paint routine is responsible for
    // making the OpenGL calls to draw the object to the screen.
    virtual void paint(void) = 0;

    //ACCESSOR
    BoundingBox* getBoundingBox() const { return boundingBox; }
    //MODIFY
    void setBoundingBox(const BoundingBox &bb) { boundingBox->Set(bb.getMin(), bb.getMax()); }
    int pushTransformPrimitive(const Transform &trans);

    static Object3DVector gridTransform;
protected:
    Material *material;
    BoundingBox *boundingBox;
};
#endif