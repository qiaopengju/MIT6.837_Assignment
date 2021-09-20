#include <cstdlib>
#include <cassert>
#include <ctime>
#include "ifs.h"
#include "matrix.h"
#include "vectors.h"

Ifs::Ifs(char* input_file, int num_points, int num_iters){
    this->num_points = num_points;
    this->num_iters = num_iters;
    //open the file
    FILE* input = fopen(input_file, "r");
    assert(input != NULL);

    //read the number of transforms
    fscanf(input, "%d", &this->n);
    this->trans = new Matrix[n];
    this->probability = new float[n];

    //read in the transforms
    for (int i = 0; i < this->n; i++){
        fscanf(input, "%f", &probability[i]);
        trans[i].Read3x3(input);
    }

    //close the file
    fclose(input);
}

void Ifs::render(Image &img){
    for (int i = 0; i < this->num_points; i++){   //travel each random point
        Vec2f rand_point(drand48(), drand48());
        for (int j = 0; j < num_iters; j++){
            // random choose a transform via probability
            int k(0);
            float sum(0), t(drand48());
            for (; k < n; k++){
                sum += probability[k];
                if (sum > t) break;
            }
            trans[k].Transform(rand_point); //transform
        }
        img.SetPixel(rand_point.x() * img.Width(), rand_point.y()*img.Height(), Vec3f());
    }
}