#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "scene_parser.h"
#include "raytracer.h"
#include "image.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "group.h"
#include "sphere.h"
#include "light.h"
#include "glCanvas.h"

GLCanvas glCanvas;

void render();

int main(int argc, char *argv[]){
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
        } else if (!strcmp(argv[i], "-gui")){
            gl_preview = true;
        } else if (!strcmp(argv[i], "-tessellation")){
            i++; assert(i < argc);
            int theta = atoi(argv[i]);
            i++; assert(i < argc);
            int phi = atoi(argv[i]);
            Sphere::gl_set_theta_phi(theta, phi);
        } else if (!strcmp(argv[i], "-gouraud")){
            gouraud = true;
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
    GLCanvas::scene = new SceneParser(input_file);
    if (gl_preview){
        glCanvas.initialize(GLCanvas::scene, render);
    } else {
        render();
    }


    return 0;
}