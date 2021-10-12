#include "ray.h"
#include "hit.h"
#include "scene_parser.h"

extern int width, height, max_bounces;
extern char *input_file, *output_file, *depth_file, *normal_file;
extern bool shade_back, gl_preview, gouraud, shadow;
extern float depth_min, depth_max, cutoff_weight;

extern void render();

class RayTracer{
public:
    //CONSTRUCTOR
    RayTracer(SceneParser *scene, int max_bounces, float cutoff_weight, bool shadows); 
    ~RayTracer();

    Vec3f traceRay(Ray &ray, float tmin, int bounces, float weight,
        float indexOfRefraction, Hit &hit) const; 
    Vec3f mirrorDirection(const Vec3f &normal, const Vec3f &incoming);
    bool transmittedDirection(const Vec3f &normal, const Vec3f &incoming,
        float index_i, float index_t, Vec3f &transmitted);
    //保存光线数据
private:
    SceneParser *scene;
    int max_bounces;
    float cutoff_weight;
    float epsilon;
    bool shadows;
    Vec3f *light_dir;
    Vec3f *light_color;
};