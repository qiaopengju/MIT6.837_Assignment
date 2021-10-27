#ifndef SAMPLER_H
#define SAMPLER_H

#include "sample.h"
#include "film.h"
#include "time.h"

extern bool random_samples, uniform_samplers, jittered_samplers;
extern char *samples_file;
extern int sample_zoom;

class Sampler{
public:
    Sampler() = default;
    virtual ~Sampler(){
        delete [] sample_pos;
        delete film;
    }
    // returns the 2D offset for the specified sample.
    Vec2f getsamplePosition(int n);
    virtual void updateSampleOffset() { }
    Film *getFilm() const { return film; }

    static int numSamples;
protected:
    Film *film;
    int width, height;
    Vec2f *sample_pos;
};

class RandomSampler : public Sampler{
public:
    RandomSampler(int _width, int _height);

    void updateSampleOffset();
};

class UniformSampler : public Sampler{
public:
    UniformSampler(int _width, int _height);
private:
    int column_sample_n;
};

class JitteredSampler : public Sampler{
public:
    JitteredSampler(int _width, int _height);
    void updateSampleOffset();
private:
    int column_sample_n;
};
#endif