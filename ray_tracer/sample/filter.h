#ifndef FILTER_H
#define FILTER_H
#include "vectors.h"

class Film;
extern bool box_filter, tent_filter, gaussian_filter;
extern int filter_zoom;
extern float gaussian_sigma, filter_radius;
extern char *filter_file;

class Filter{
public:
    Filter() = default;

    //computes the appropriately filtered color for pixel (i,j) 
    //from the samples stored in the Film instance
    Vec3f getColor(int i, int j, Film *film);
    //returns the weight for point (x + pixel center, y + pixel center
    virtual float getWeight(float x, float y) = 0;
    virtual int getSupportRadius() = 0;
};

class BoxFilter : public Filter{
public:
    BoxFilter(float radius = 0){ this->radius = radius; }
    float getWeight(float x, float y);
    int getSupportRadius(){ return ceil(radius - 0.5); }
private:
    float radius;
};

class TentFilter: public Filter{
public:
    TentFilter(float radius = 0){ this->radius = radius; }
    float getWeight(float x, float y);
    int getSupportRadius(){ return ceil(radius - 0.5); }
private:
    float radius;
};

class GaussianFilter: public Filter{
public:
    GaussianFilter(float _sigma) : sigma{_sigma} {}
    float getWeight(float x, float y);
    int getSupportRadius(){ return ceil(2*sigma - 0.5); }
private:
    float sigma;
};

#endif