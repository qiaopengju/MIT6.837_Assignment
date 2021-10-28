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
#include "rayTree.h"
#include "matrix.h"
#include "marchingInfo.h"
#include "raytracing_stats.h"
#include "sample/sampler.h"
#include "sample/filter.h"

int width(100), height(100), max_bounces(0), nx(0), ny(0), nz(0), sample_zoom(0), filter_zoom(0);
char *input_file(NULL), *output_file(NULL), *depth_file(NULL), *normal_file(NULL), *samples_file(NULL), *filter_file(NULL);
bool shade_back(false), gl_preview(false), gouraud(false), shadow(false), visualize_grid(false);
bool box_filter(false), tent_filter(false), gaussian_filter(false);
bool random_samples(false), uniform_samplers(false), jittered_samplers(false);
float depth_min(0), depth_max(1), cutoff_weight(0);
float gaussian_sigma(0), filter_radius(0);

//static value
int Sampler::numSamples{1};
Grid* RayTracer::grid;

void render(){
    RayTracer raytracer(GLCanvas::scene, max_bounces, cutoff_weight, shadow);
    Camera* camera = GLCanvas::scene->getCamera();
    Group* group = GLCanvas::scene->getGroup();
    Image *image, *image_depth, *image_normal;
    //sampler
    Sampler *sampler;
    if (random_samples) sampler = new RandomSampler(width, height);
    else if (uniform_samplers) sampler = new UniformSampler(width, height);
    else if (jittered_samplers) sampler = new JitteredSampler(width, height);
    else sampler = new UniformSampler(width, height);
    //filter 默认boxfilter
    Filter::height = height;
    Filter::width = width;
    Filter *filter;
    if (box_filter) filter = new BoxFilter(filter_radius);
    else if (tent_filter) filter = new TentFilter(filter_radius);
    else if (gaussian_filter) filter = new GaussianFilter(gaussian_sigma);
    else filter = new BoxFilter(filter_radius);

    //initialize image background color
    if (output_file) {
        image = new Image(width, height);
        image->SetAllPixels(GLCanvas::scene->getBackgroundColor());
    }
    if (depth_file) {
        image_depth = new Image(width, height);
        image_depth->SetAllPixels(GLCanvas::scene->getBackgroundColor());
    }
    if (normal_file){
        image_normal = new Image(width, height);
        image_depth->SetAllPixels(GLCanvas::scene->getBackgroundColor());
    }
    //render
    //Initialize raytracing stats
    RayTracingStats::Initialize(width, height, group->getBoundingBox(), nx, ny, nz);
    //generate ray
    Vec2f pixel_size = Vec2f(1.f / width, 1.f / height);
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            Ray r;
            Hit h;
            if (sampler) { //sampler
                sampler->updateSampleOffset();
                for (int s = 0; s < sampler->numSamples; s++){
                    Vec2f s_pos = sampler->getsamplePosition(s);
                    float off_x = pixel_size.x() * s_pos.x();
                    float off_y = pixel_size.y() * s_pos.y();
                    r = camera->generateRay(Vec2f((float)i/width + off_x, (float)j/height + off_y));
                    h.set(INFINITY, NULL, r);
                    Vec3f color = raytracer.traceRay(r, raytracer.getEpsilon(), 0, 1, 1, h);
                    // if (color != GLCanvas::scene->getBackgroundColor())
                    sampler->getFilm()->setSample(i, j, s, s_pos, color);
                }
            }
            if (output_file) image->SetPixel(i, j, filter->getColor(i, j, sampler->getFilm()));
            if (h.getMaterial()){             //光线与物体相交
                if (depth_file != NULL){ //render depth
                    float t = h.getT();
                    if (t >= depth_min && t <= depth_max){
                        t = 1 - (t - depth_min) / (depth_max - depth_min);
                        image_depth->SetPixel(i, j, Vec3f(t, t, t));
                    }
                }
                if (normal_file){ //render normal
                    Vec3f normal = h.getNormal();
                    image_normal->SetPixel(i, j, Vec3f(abs(normal.r()), abs(normal.g()), abs(normal.b())));
                }
            }
        }
    }
    RayTracingStats::PrintStatistics();

    //output image to file
    if (output_file){
        Image::SaveImage(output_file, image);
        delete image;
    }
    if (depth_file){
        Image::SaveImage(depth_file, image_depth);
        delete image_depth;
    }
    if (normal_file != NULL){
        Image::SaveImage(normal_file, image_normal);
        delete image_normal;
    }
    if (samples_file) sampler->getFilm()->renderSamples(samples_file, sample_zoom);
    if (filter_file && filter) sampler->getFilm()->renderFilter(filter_file, filter_zoom, filter);
    if (sampler) delete sampler;
    if (filter) delete filter;
}

void traceRayFunc(float x, float y){
    RayTracer raytracer(GLCanvas::scene, max_bounces, cutoff_weight, shadow);
    Hit h(INFINITY, NULL);
    Ray r = GLCanvas::scene->getCamera()->generateRay(Vec2f(x, y));
    raytracer.traceRay(r, raytracer.getEpsilon(), 0, 1, 0, h);

    //ray grid marcing
    if (raytracer.grid != NULL) {
        Hit hitGrid(INFINITY, NULL);
        raytracer.grid->intersect(r, hitGrid, raytracer.getEpsilon());
    }
}

RayTracer::RayTracer(SceneParser *scene, int max_bounces, float cutoff_weight, bool shadows){
    this->scene = scene;
    this->max_bounces = max_bounces;
    this->cutoff_weight = cutoff_weight;
    this->shadows = shadows;
    epsilon = 0.001;

    int num_light = scene->getNumLights();
    light_dir = new Vec3f[num_light];
    light_color = new Vec3f[num_light];
}

RayTracer::~RayTracer(){
    delete [] light_dir;
    delete [] light_color;
}

//bounce from 0 - max_bounce
Vec3f RayTracer::traceRay(const Ray &ray, float tmin, int bounces, float weight,
        float indexOfRefraction, Hit &hit) const{
    //return if max bounce
    if (bounces > max_bounces || weight <= cutoff_weight) return Vec3f(0, 0, 0);
    RayTracingStats::IncrementNumNonShadowRays();

    Camera* camera = scene->getCamera();
    Group* group = scene->getGroup();
    //intersect all objects
    bool hitFlag;
    if (grid) hitFlag = grid->intersect(ray, hit, tmin);
    else hitFlag = group->intersect(ray, hit, tmin);
    // RayTree: main segment
    if (bounces == 0) RayTree::SetMainSegment(ray, 0, hit.getT());
    if (!hitFlag) return scene->getBackgroundColor();

    //assert(hit.getMaterial() != NULL);
    Vec3f result = scene->getAmbientLight() * hit.getMaterial()->getDiffuseColor(hit.getIntersectionPoint());
    Vec3f hit_pos = ray.pointAtParameter(hit.getT());
    //cast shadow ray
    for (int i = 0; i < scene->getNumLights(); i++){ //for every light
        float distace2Light = scene->getLight(i)->distace2Light(hit_pos);
        scene->getLight(i)->getIllumination(hit_pos, light_dir[i], light_color[i], distace2Light);
        Vec3f directionToLight; 
        bool isPointLight = distace2Light != INFINITY;
        if (!isPointLight){ //direction light
            directionToLight = light_dir[i];
        } else { //point light
            directionToLight = scene->getLight(i)->getLightPos() - hit_pos;
        }
        directionToLight.Normalize();

        bool inShadow(false);
        Ray rayShadow(hit_pos, directionToLight);
        Hit hitShadow(distace2Light, NULL);
        if (shadow){ //计算shadow
            RayTracingStats::IncrementNumShadowRays();
            if (grid){
                inShadow = grid->intersect(rayShadow, hitShadow, tmin);
            } else{
                inShadow = group->intersectShadowRay(rayShadow, hitShadow, tmin);
            }
            //=====================
            // RayTree: shadow ray 
            RayTree::AddShadowSegment(rayShadow, 0, hitShadow.getT());
            if (inShadow && isPointLight){
                float distance2Shadow = (rayShadow.pointAtParameter(hitShadow.getT()) - hit_pos).Length();
                if (distance2Shadow > distace2Light) inShadow = false;
            }
        }
        if (!shadows || !inShadow){ //如果不用显示shadow或者物体在改光线下没有被遮挡
            result += hit.getMaterial()->Shade(ray, hit, light_dir[i], light_color[i]); //光线颜色乘以权重
        }
    }

    //reflect
    if (bounces <= max_bounces && hit.getMaterial()->getReflectiveColor() != Vec3f(0,0,0)){
        Vec3f reflect = mirrorDirection(hit.getNormal(), ray.getDirection());
        Ray rR(hit_pos, reflect);
        Hit hR(INFINITY, NULL);
        float reWeight = hit.getMaterial()->getReflectiveColor().Length();
        result += (traceRay(rR, tmin, bounces+1, weight*reWeight, indexOfRefraction, hR) * hit.getMaterial()->getReflectiveColor());
        //=====================
        // RayTree: reflect ray 
        RayTree::AddReflectedSegment(rR, 0, hR.getT());
    }
    //refract
    if (bounces <= max_bounces && hit.getMaterial()->getTransparentColor() != Vec3f(0,0,0)){
        Vec3f refract;
        float index_i, index_t;
        if (ray.getDirection().Dot3(hit.getNormal()) < 0){ //光线入射透明材料
            index_i = 1;
            index_t = hit.getMaterial()->getIndexOfRefraction();
        } else { //光线出射透明材料
            index_i = hit.getMaterial()->getIndexOfRefraction();
            index_t = 1;
        }
        bool shouldTransparent = transmittedDirection(hit.getNormal(), ray.getDirection(), index_i, index_t, refract);
        if (shouldTransparent){ //应该折射
            Ray rR(hit_pos, refract);
            Hit hR(INFINITY, NULL);
            float trWeight = hit.getMaterial()->getTransparentColor().Length();
            result += (traceRay(rR, tmin, bounces+1, weight*trWeight, hit.getMaterial()->getIndexOfRefraction(), hR) * hit.getMaterial()->getTransparentColor());
            //=====================
            // RayTree: refract ray 
            RayTree::AddTransmittedSegment(rR, 0, hR.getT());
        } //else{ //inner reflect 内全反射
            // Vec3f reflect = mirrorDirection(-1*hit.getNormal(), ray.getDirection());
            // Ray rR(hit_pos, reflect);
            // float reWeight = hit.getMaterial()->getReflectiveColor().Length();
            // result += (traceRay(rR, tmin, bounces+1, weight*reWeight, indexOfRefraction, hR) * hit.getMaterial()->getReflectiveColor());
            // //=====================
            // // RayTree: inner reflect ray 
            // RayTree::AddReflectedSegment(rR, 0, hR.getT());
        // }
    }
    return result;
}

Vec3f RayTracer::mirrorDirection(const Vec3f &normal, const Vec3f &incoming) const{
    Vec3f norNormal = normal; norNormal.Normalize();
    Vec3f norIncoming = incoming; norIncoming.Normalize();
    Vec3f reflect = norIncoming - 2 * norIncoming.Dot3(norNormal) * norNormal;
    reflect.Normalize();
    return reflect;
}

bool RayTracer::transmittedDirection(const Vec3f &normal, const Vec3f &incoming,
        float index_i, float index_t, Vec3f &transmitted) const{
    Vec3f norNormal = normal; norNormal.Normalize();
    Vec3f norIncoming = incoming; norIncoming.Negate(); norIncoming.Normalize();
    //求折射率
    assert(index_t != 0);   //分母不为零
    float index = index_i / index_t; //折射率
    float NI = norIncoming.Dot3(norNormal);
    float sq = 1 - ((index * index) * (1 - NI * NI));
    if (sq < 0) return false; //total internal reflection, 全反射
    if (NI > 0) transmitted = ((index * NI - sqrt(sq)) * norNormal) - (index * norIncoming);
    else transmitted = (index * NI + sqrt(sq)) * norNormal - (index * norIncoming);
    transmitted.Normalize();
    return true;
}