#include "filter.h"
#include "film.h"
#include "sampler.h"

Vec3f Filter::getColor(int i, int j, Film *film){
    float weight{0}, r{0};
    Vec3f result;
    do {
        for (int i = -1; i <= 1; i++){ //遍历8个方向
            for (int j = -1; j <= 1; j++){
            }
        }
        r++;
    } while (r <= getSupportRadius());
}

float BoxFilter::getWeight(float x, float y){
    if (x > radius || y > radius || x < -radius || y < -radius) return 0;
    return 1;
}

float TentFilter::getWeight(float x, float y){
    // assert(x <= getSupportRadius() + 0.5 && y <= getSupportRadius() + 0.5);
    float r2 = x*x + y*y;
    float R2 = radius * radius;
    if (r2 > R2) return 0;
    return 1.f - sqrt(r2) / sqrt(R2);
}

float GaussianFilter::getWeight(float x, float y){
    float d2 = x*x + y*y;
    // if (sqrt(d2) > 2 * sigma) return 0;
    return exp(-d2/(2*sigma*sigma));
}