#include <cstdlib>
#include <cassert>
#include "image.h"
#include "matrix.h"
#include "ifs.h"

int main(int argc, char* argv[]){
    //HANDLE COMMAND LINE ARGUMENTS
    //sample command line:
    //ifs -input fern.txt -points 10000 -iters 10 -size 100 -output fern.tga
    char *input_file(NULL), *output_file(NULL);
    int num_points(10000), num_iters(10), size(100);

    for (int i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-input")){
            i++; assert(i < argc);
            input_file = argv[i];
        } else if(!strcmp(argv[i], "-points")){
            i++; assert(i < argc);
            num_points = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-iters")){
            i++; assert(i < argc);
            num_iters = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-size")){
            i++; assert(i < argc);
            size = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-output")){
            i++; assert(i < argc);
            output_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }

    //Image instance
    Image img(size, size);
    img.SetAllPixels(Vec3f(1.0, 1.0, 1.0));
    //Ifs instance
    Ifs ifs(input_file, num_points, num_iters);
    ifs.render(img);
    const char *ext = &output_file[strlen(output_file)-4];
    if (!strcmp(ext, ".ppm")) img.SavePPM(output_file);
    if (!strcmp(ext, ".tga")) img.SaveTGA(output_file);

    return 0;
}