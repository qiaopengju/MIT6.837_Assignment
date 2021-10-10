#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include "ray.h"
#include "vectors.h"

class Camera{
    //generate rays for each screen-space coordinate, described as a Vec2f
public:
    Camera() = default;
    ~Camera() {};

    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;

    //===========================================================
    // Here are the prototypes for five pure virtual functions for
    // initializing, placing, dollying, trucking, and rotating an
    // OpenGL camera.
    virtual void glInit(int w, int h) = 0;
    virtual void glPlaceCamera(void) = 0;
    // dollyCamera: Move camera along the direction vector
    virtual void dollyCamera(float dist) = 0;
    // truckCamera: Translate camera perpendicular to the direction vector
    virtual void truckCamera(float dx, float dy) = 0;
    // rotateCamera: Rotate around the up and horizontal vectors
    virtual void rotateCamera(float rx, float ry) = 0;
};

class OrthographicCamera : public Camera{
public:
    //CONSTRUCTOR:
    //The constructor takes as input the center of the image, 
    //the direction vector, an up vector, and the image size
    OrthographicCamera(Vec3f _center, Vec3f _direction, Vec3f _up, float _size);
    ~OrthographicCamera() {}

    //generate rays for each screen-space coordinate
    Ray generateRay(Vec2f point);
    //will be useful when tracing rays through the scene
    float getTMin() const;

    // ===========================================
    // GLUT
    // ===========================================
    // Create an orthographic camera with the appropriate dimensions that
    // crops the screen in the narrowest dimension.
    void glInit(int w, int h);
    // Place an orthographic camera within an OpenGL scene
    void glPlaceCamera();
    void dollyCamera(float dist);
    void truckCamera(float dx, float dy);
    void rotateCamera(float rx, float ry);

private:
    Vec3f center, direction, up, horizontal;
    float size;
};

class PerspectiveCamera : public Camera{
public:
    //CONSTRUCTOR:
    //The constructor takes as input the center of the image, 
    //the direction vector, an up vector, and the image size
    PerspectiveCamera(Vec3f _center, Vec3f _direction, Vec3f _up, float angle_randians);
    ~PerspectiveCamera() {}

    //generate rays for each screen-space coordinate
    Ray generateRay(Vec2f point);
    //will be useful when tracing rays through the scene
    float getTMin() const;

    // ===========================================
    // GLUT
    // ===========================================
    void glInit(int w, int h);
    void glPlaceCamera();
    void dollyCamera(float dist);
    void truckCamera(float dx, float dy);
    void rotateCamera(float rx, float ry);
private:
    Vec3f center, direction, up, horizontal;
    float angle_randians;
};
#endif