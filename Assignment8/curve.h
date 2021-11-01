#ifndef CURVE_H
#define CURVE_H
#define GL_SILENCE_DEPRECATION
#include "GL/glut.h"
#include <vector>
#include <vector>
#include "spline.h"
#include "arg_parser.h"

inline int factorial(int n){
    int result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

class Curve : public Spline{
public:
    Curve() = default;

    virtual vector<Vec2f> getPoint(float t) = 0;

    void Paint(ArgParser *args){
        //Draw control points
        glPointSize(10);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        for (int i = 0; i < vNum; i++)
            glVertex2f(vertexs[i].x(), vertexs[i].y());
        glEnd();
        //Draw control polygon
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        for (int i = 1; i < vNum; i++){ //begin from 1
            glVertex2f(vertexs[i-1].x(), vertexs[i-1].y());
            glVertex2f(vertexs[i].x(), vertexs[i].y());
        }
        glEnd();
        //Draw Curves
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        float step = 1.f / args->curve_tessellation;
        for (float t = 0; t < 1; t += step){
            vector<Vec2f> v0 = getPoint(t);
            vector<Vec2f> v1;
            if (t + step <= 1) v1 = getPoint(t + step);
            else v1 = getPoint(1);
            for (int i = 0; i < v0.size(); i++){
                glVertex2f(v0[i].x(), v0[i].y());
                glVertex2f(v1[i].x(), v1[i].y());
            }
        }
        glEnd();
    }
};

class BezierCurve : public Curve{
public:
    BezierCurve(int vNum){
        // vertexs = new Vec3f[vNum];
        vertexs.resize(sizeof(Vec3f) * vNum);
        this->vNum = vNum;
    }
    void set(int i, Vec3f v){
        assert(i >= 0 && i < vNum);
        vertexs[i] = v;
    }
    //4个点为一组
    vector<Vec2f> getPoint(float t){
        int N = 3;
        vector<Vec2f> v;
        for (int i = 0; i < vNum; i += 3){
            Vec3f result;
            for (int j = 0; j < 4; j++){
                if (i + j < vNum) result += powf(t, j) * powf(1.f - t, N - j) * factorial(N) / (factorial(N - j) * factorial(j)) * vertexs[i + j];
                else result += powf(t, j) * powf(1.f - t, N - j) * factorial(N) / (factorial(N - j) * factorial(j)) * vertexs[vNum - 1];
            }
            v.push_back(Vec2f(result.x(), result.y()));
        }
        return v;
    }
};

class BSplineCurve : public Curve{
public:
    BSplineCurve(int vNum){
        // vertexs = new Vec3f[vNum];
        vertexs.resize(sizeof(Vec3f) * vNum);
        this->vNum = vNum;
    }
    void set(int i, Vec3f v){
        assert(i >= 0 && i < vNum);
        vertexs[i] = v;
    }
    vector<Vec2f> getPoint(float t){
        float a0 = powf(1.f - t, 3) / 6.f;
        float a1 = (3*t*t*t - 6*t*t + 4) / 6.f;
        float a2 = (-3*t*t*t + 3*t*t + 3*t + 1) / 6.f;
        float a3 = t*t*t / 6;
        float a[] = {a0, a1, a2, a3};
        vector<Vec2f> v;
        // for (int i = 3; i < vNum; i++){
        //     Vec3f result = a0 * vertexs[i-3] + a1 * vertexs[i-2] + a2 * vertexs[i-1] + a3 * vertexs[i];
        //     v.push_back(Vec2f(result.x(), result.y()));
        // }
        for (int i = 0; i < vNum; i++){
            Vec3f result;
            for (int j = 0; j < 4; j++){
                if (i + j < vNum) result += a[j] * vertexs[i + j];
                else return v;
            }
            v.push_back(Vec2f(result.x(), result.y()));
        }
        return v;
    }
};
#endif