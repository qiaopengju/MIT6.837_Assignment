#include <iostream>
#include "raytracer.h"
#include "scene_parser.h"
#include "image.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "group.h"
#include "sphere.h"
#include "light.h"
#include "glCanvas.h"


int width(100), height(100), max_bounces;
char *input_file(NULL), *output_file(NULL), *depth_file(NULL), *normal_file(NULL);
bool shade_back(false), gl_preview(false), gouraud(false), shadow(false);
float depth_min(0), depth_max(1), cutoff_weight;

void render(){
    Camera* camera = GLCanvas::scene->getCamera();
    Group* group = GLCanvas::scene->getGroup();
    Image *image, *image_depth, *image_normal;
    if (output_file != NULL) {
        image = new Image(width, height);
        image->SetAllPixels(GLCanvas::scene->getBackgroundColor());
    }
    if (depth_file != NULL) {
        image_depth = new Image(width, height);
        image_depth->SetAllPixels(GLCanvas::scene->getBackgroundColor());
    }
    if (normal_file != NULL){
        image_normal = new Image(width, height);
        image_depth->SetAllPixels(GLCanvas::scene->getBackgroundColor());
    }
    //get light
    int num_light = GLCanvas::scene->getNumLights();
    Vec3f *light_dir = new Vec3f[num_light];
    Vec3f *light_color = new Vec3f[num_light];
    //render
    //generate ray
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            Ray r = camera->generateRay(Vec2f((float)i/width, (float)j/height));
            Hit h;
            if (group->intersect(r, h, camera->getTMin())){             //光线与物体相交
                assert(h.getMaterial() != NULL);
                Vec3f hit_pos = r.pointAtParameter(h.getT());
                Vec3f pixel_color;
                //diffuse shading
                for (int i = 0; i < num_light; i++){                    //读取光线数据
                    GLCanvas::scene->getLight(i)->getIllumination(hit_pos, light_dir[i], light_color[i]);
                    pixel_color += h.getMaterial()->Shade(r, h, light_dir[i], light_color[i]);
                }
                //pixel color = diffuse + ambient + specular
                pixel_color += GLCanvas::scene->getAmbientLight() * h.getMaterial()->getDiffuseColor();
                image->SetPixel(i, j, pixel_color);

                if (depth_file != NULL){ //render depth
                    float t = h.getT();
                    if (t >= depth_min && t <= depth_max){
                        t = 1 - (t - depth_min) / (depth_max - depth_min);
                        image_depth->SetPixel(i, j, Vec3f(t, t, t));
                    }
                }
                if (normal_file != NULL){ //render normal
                    Vec3f normal = h.getNormal();
                    float r = abs(normal.r()); 
                    float g = abs(normal.g()); 
                    float b = abs(normal.b()); 
                    image_normal->SetPixel(i, j, Vec3f(r, g, b));
                }
            }
        }
    }
    delete [] light_dir;
    delete [] light_color;

    //output image to file
    char *ext = &output_file[strlen(output_file) - 4];
    if (!strcmp(ext, ".ppm")) image->SavePPM(output_file);
    else if (!strcmp(ext, ".tga")) {
        image->SaveTGA(output_file);
    } else {
        printf("error output image format\n");
        assert(0);
    }
    if (depth_file != NULL){
        char *ext_depth = &depth_file[strlen(depth_file) - 4];
        if (!strcmp(ext_depth, ".ppm")) image_depth->SavePPM(depth_file);
        else if (!strcmp(ext_depth, ".tga")) image_depth->SaveTGA(depth_file);
        else {
            printf("error depth image format\n");
            assert(0);
        }
    }
    if (normal_file != NULL){
        char *ext_normal = &normal_file[strlen(normal_file) - 4];
        if (!strcmp(ext_normal, ".ppm")) image_normal->SavePPM(normal_file);
        else if (!strcmp(ext_normal, ".tga")) image_normal->SaveTGA(normal_file);
        else {
            printf("error normal image format\n");
            assert(0);
        }
    }
    printf("output done!\n");
}

RayTracer::RayTracer(SceneParser *scene, int max_bounces, float cutoff_weight, bool shadows){
    this->scene = scene;
    this->max_bounces = max_bounces;
    this->cutoff_weight = cutoff_weight;
    this->shadows = shadows;
    epsilon = 0;

    int num_light = GLCanvas::scene->getNumLights();
    Vec3f *light_dir = new Vec3f[num_light];
    Vec3f *light_color = new Vec3f[num_light];
}

RayTracer::~RayTracer(){
    delete [] light_dir;
    delete [] light_color;
}

Vec3f RayTracer::traceRay(Ray &ray, float tmin, int bounces, float weight,
        float indexOfRefraction, Hit &hit) const{
    Camera* camera = GLCanvas::scene->getCamera();
    Group* group = GLCanvas::scene->getGroup();
    int num_light = scene->getNumLights();
    Vec3f *light_dir = new Vec3f[num_light];
    Vec3f *light_color = new Vec3f[num_light];

    //=====================
    //intersect all objects
    if (!group->intersect(ray, hit, camera->getTMin())){ //光线与物体未相交 
    }
    assert(hit.getMaterial() != NULL);
    Vec3f result = scene->getAmbientLight() * hit.getMaterial()->getDiffuseColor();
    //=====================
    //cast shadow ray
    //=====================
    for (int i = 0; i < scene->getNumLights(); i++){ //for every light
        Vec3f hitPoint{ray.pointAtParameter(hit.getT())};
        Vec3f directionToLight{light_dir[i]}; 
        directionToLight.Negate(); 
        directionToLight.Normalize();

        Ray ray2(hitPoint, directionToLight);
        Hit hit2;
        if (!shadows || !group->shadowIntersect(ray2, hit2, epsilon)){ //如果不用显示shadow或者物体在改光线下没有被遮挡
            result += hit.getMaterial()->Shade(ray, hit, directionToLight, light_color[i]);
        }
    }
    //=====================
    //mirror
    //=====================
    if (hit.getMaterial()->getReflectiveColor() != Vec3f(0,0,0)){
    }
    //=====================
    //transparent
    //=====================
    if (hit.getMaterial()->getTransparentColor() != Vec3f(0,0,0)){
    }
    return result;
}

Vec3f RayTracer::mirrorDirection(const Vec3f &normal, const Vec3f &incoming){
}

bool RayTracer::transmittedDirection(const Vec3f &normal, const Vec3f &incoming,
    float index_i, float index_t, Vec3f &transmitted){
}