#include "filter.h"
#include "film.h"
#include "sampler.h"

int Filter::width, Filter::height;

Vec3f Filter::getColor(int i, int j, Film *film){
    float weight{0};
    Vec3f result;
    for (int r = 0; r <= getSupportRadius(); r++){
        for (int x = -1; x <= 1; x++){
            for (int y = -1; y <= 1; y++){
                int ix = x*r + i;
                int iy = y*r + j;
                if (ix < 0 || ix >= width || iy < 0 || iy >= height) continue;
                for (int s = 0; s < Sampler::numSamples; s++){
                    Sample tmpS = film->getSample(ix, iy, s);
                    Vec2f pos = tmpS.getPosition();
                    float w = getWeight(x*r + pos.x() - 0.5, y*r + pos.x() - 0.5);
                    result += tmpS.getColor() * w;
                    weight += w;
                }
            }
        }
    }
    result /= weight;
    return result;
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