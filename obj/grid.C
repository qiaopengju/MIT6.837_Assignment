#include "grid.h"

Grid::Grid(BoundingBox *bb, int nx, int ny, int nz){
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
    opaque = new bool[nx * ny * nz];
    boundingBox = bb;
}
Grid::~Grid(){
    delete opaque;
}

bool Grid::intersect(const Ray &r, Hit &h, float tmin){
}
// The paint routine is responsible for
// making the OpenGL calls to draw the object to the screen.
void Grid::paint(void){

}