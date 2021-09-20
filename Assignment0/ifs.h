#ifndef IFS_H
#define IFS_H

#include "matrix.h"
#include "image.h"

class Ifs{
    int n;              //the number of transformations
    int num_points, num_iters;
    Matrix *trans;      //n transformations
    float *probability; //probabilities for choosing a transformation
public:
    //consturctor
    Ifs(char* input_file, int num_points, int num_iters);
    //destructor
    ~Ifs(){ delete [] trans; delete [] probability;}
    void render(Image&);
};
#endif