#include "sampler.h"

Vec2f Sampler::getsamplePosition(int n){
    assert(n >= 0 && n < Sampler::numSamples);
    return sample_pos[n];
}

RandomSampler::RandomSampler(int _width, int _height){
    width = _width;
    height = _height;
    sample_pos = new Vec2f[Sampler::numSamples];
    film = new Film(_width, _height, Sampler::numSamples);
}

void RandomSampler::updateSampleOffset() {
    srand((unsigned) time(NULL));
    for (int i = 0; i < Sampler::numSamples; i++)
        sample_pos[i].Set((float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
}

UniformSampler::UniformSampler(int _width, int _height){
    width = _width;
    height = _height;
    column_sample_n = sqrt(Sampler::numSamples);
    sample_pos = new Vec2f[Sampler::numSamples];
    film = new Film(_width, _height, Sampler::numSamples);
    float offset = 1.f / (float)(column_sample_n + 1);
    for (int i = 0; i < column_sample_n; i++)
        for (int j = 0; j < column_sample_n; j++)
            sample_pos[i * column_sample_n + j] = Vec2f((j+1) * offset, (i+1) * offset);
}

JitteredSampler::JitteredSampler(int _width, int _height){
    width = _width;
    height = _height;
    column_sample_n = sqrt(Sampler::numSamples);
    sample_pos = new Vec2f[Sampler::numSamples];
    film = new Film(_width, _height, Sampler::numSamples);
}

void JitteredSampler::updateSampleOffset() {
    srand((unsigned) time(NULL));
    float offset = 1.f / (float)(column_sample_n + 1);
    for (int i = 0; i < column_sample_n; i++)
        for (int j = 0; j < column_sample_n; j++){
            float roff_x = ((float)random()/RAND_MAX - 0.5) * offset;
            float roff_y = ((float)random()/RAND_MAX - 0.5) * offset;
            // printf("OFFSET: %f %f\n", roff_x, roff_y);
            sample_pos[i * column_sample_n + j] = Vec2f((j+1) * offset + roff_x, (i+1) * offset + roff_y);
        }
}