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

int main(int argc, char *argv[]){
    char *input_file(NULL), *output_file(NULL), *depth_file(NULL);
    int width(100), height(100);
    float depth_min(0), depth_max(1);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert (i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc); 
            width = atoi(argv[i]);
            i++; assert (i < argc); 
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc); 
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++; assert (i < argc); 
            depth_min = atof(argv[i]);
            i++; assert (i < argc); 
            depth_max = atof(argv[i]);
            i++; assert (i < argc); 
            depth_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
    SceneParser sceneParser(input_file);
    Camera* camera = sceneParser.getCamera();
    Group* group = sceneParser.getGroup();
    Image image(width, height), image_depth(width, height);

    //render
    image.SetAllPixels(sceneParser.getBackgroundColor());
    image_depth.SetAllPixels(sceneParser.getBackgroundColor());
    //generate ray
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            Ray r = camera->generateRay(Vec2f((float)i/width, (float)j/height));
            Hit h;
            if (group->intersect(r, h, camera->getTMin())){
                assert(h.getMaterial() != NULL);
                image.SetPixel(i, j, h.getMaterial()->getDiffuseColor());
                float t = h.getT();
                if (t >= depth_min && t <= depth_max){
                    t = 1 - (t - depth_min) / (depth_max - depth_min);
                    image_depth.SetPixel(i, j, Vec3f(t, t, t));
                }
                //image_depth.SetPixel(i, j, )
            }
        }
    }

    //output image to file
    char *ext = &output_file[strlen(output_file) - 4];
    char *ext_depth = &depth_file[strlen(depth_file) - 4];
    if (!strcmp(ext, ".ppm")) image.SavePPM(output_file);
    else if (!strcmp(ext, ".tga")) image.SaveTGA(output_file);
    else {
        printf("error output image format\n");
        assert(0);
    }
    if (!strcmp(ext_depth, ".ppm")) image_depth.SavePPM(depth_file);
    else if (!strcmp(ext_depth, ".tga")) image_depth.SaveTGA(depth_file);
    else {
        printf("error depth image format\n");
        assert(0);
    }

    return 0;
}