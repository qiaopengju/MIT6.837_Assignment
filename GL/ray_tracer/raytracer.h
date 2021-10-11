#include "scene_parser.h"

extern int width, height;
extern char *input_file, *output_file, *depth_file, *normal_file;
extern bool shade_back, gl_preview, gouraud;
extern float depth_min, depth_max;
extern SceneParser *sceneParser;

extern void render();