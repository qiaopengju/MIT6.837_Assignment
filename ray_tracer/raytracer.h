#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include "ray.h"
#include "hit.h"
#include "scene_parser.h"

extern int width, height, max_bounces;
extern char *input_file, *output_file, *depth_file, *normal_file;
extern bool shade_back, gl_preview, gouraud, shadow;
extern float depth_min, depth_max, cutoff_weight;

extern void render();
extern void traceRayFunc(float , float);

class RayTracer{
public:
    //CONSTRUCTOR
    RayTracer(SceneParser *scene, int max_bounces, float cutoff_weight, bool shadows); 
    ~RayTracer();

    Vec3f traceRay(const Ray &ray, float tmin, int bounces, float weight,
        float indexOfRefraction, Hit &hit) const; 
    Vec3f mirrorDirection(const Vec3f &normal, const Vec3f &incoming) const;
    bool transmittedDirection(const Vec3f &normal, const Vec3f &incoming,
        float index_i, float index_t, Vec3f &transmitted) const;
    //ACCESSOR
    float getEpsilon() const { return epsilon; }
private:
    SceneParser *scene;
    int max_bounces;
    float cutoff_weight;
    float epsilon;
    bool shadows;
    Vec3f *light_dir;
    Vec3f *light_color;
};
#endif