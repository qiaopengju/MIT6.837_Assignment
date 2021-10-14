#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.h"
#include "vectors.h"

class Sphere : public Object3D{
public:
    //CONSTRUCTOR
    Sphere(Vec3f _center, float _radius, Material *_material);
    ~Sphere();

    static void gl_set_theta_phi(const int &theta, const int &phi);
    Vec3f getPoint(float _theta, float _phi);
    //virtual
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    void insertIntoGrid(Grid *g, Matrix *m);
private:
    Vec3f center;
    float radius;
    static int phi, theta;
    void renderVertexGourad(Vec3f v);
};
#endif