#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "scene_parser.h"
#include "image.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "group.h"
#include "light.h"

int main(int argc, char *argv[]){
    char *input_file(NULL), *output_file(NULL), *depth_file(NULL), *normal_file(NULL);
    int width(100), height(100);
    float depth_min(0), depth_max(1);
    bool shade_back(false);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert(i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert(i < argc); 
            width = atoi(argv[i]);
            i++; assert(i < argc); 
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert(i < argc); 
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++; assert(i < argc); 
            depth_min = atof(argv[i]);
            i++; assert(i < argc); 
            depth_max = atof(argv[i]);
            i++; assert(i < argc); 
            depth_file = argv[i];
        } else if (!strcmp(argv[i], "-normals")) {
            i++; assert(i < argc);
            normal_file = argv[i];
        } else if (!strcmp(argv[i], "-shade_back")){
            shade_back = true;
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
    SceneParser sceneParser(input_file);
    Camera* camera = sceneParser.getCamera();
    Group* group = sceneParser.getGroup();
    Image *image, *image_depth, *image_normal;
    if (output_file != NULL) {
        image = new Image(width, height);
        image->SetAllPixels(sceneParser.getBackgroundColor());
    }
    if (depth_file != NULL) {
        image_depth = new Image(width, height);
        image_depth->SetAllPixels(sceneParser.getBackgroundColor());
    }
    if (normal_file != NULL){
        image_normal = new Image(width, height);
        image_depth->SetAllPixels(sceneParser.getBackgroundColor());
    }

    //get light
    int num_light = sceneParser.getNumLights();
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
                Vec3f ambient_color = sceneParser.getAmbientLight();    //读取环境光
                //caculate diffuse color
                Vec3f diffuse_color;                                    //(0, 0, 0)
                Vec3f hit_pos = r.pointAtParameter(h.getT());
                //diffuse shading
                for (int i = 0; i < num_light; i++){                    //读取光线数据
                    sceneParser.getLight(i)->getIllumination(hit_pos, light_dir[i], light_color[i]);
                    float diffuse = light_dir[i].Dot3(h.getNormal());
                    if (diffuse < 0){ //点积为负，光在物体背面
                        if (shade_back) diffuse = -diffuse;             //渲染背面
                        else diffuse = 0;                               //不渲染背面，diffuse为0
                    }
                    diffuse_color += diffuse * light_color[i];
                }
                //pixel color = diffuse + ambient + specular
                Vec3f pixel_color = (diffuse_color + ambient_color) * h.getMaterial()->getDiffuseColor();
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
    printf("output\n");

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

    delete [] light_dir;
    delete [] light_color;

    return 0;
}