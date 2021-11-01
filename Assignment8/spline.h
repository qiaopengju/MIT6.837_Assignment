#ifndef SPLINE_H
#define SPLINE_H
#include <vector>
#include "vectors.h"
#include "triangle_mesh.h"

class Spline {
public:
    Spline(){ }
    // FOR VISUALIZATION
    virtual void Paint(ArgParser *args) { }
    
    // FOR CONVERTING BETWEEN SPLINE TYPES
    virtual void OutputBezier(FILE *file) { }
    virtual void OutputBSpline(FILE *file) { }
    
    // FOR CONTROL POINT PICKING
    virtual int getNumVertices() { return vNum; }
    virtual Vec3f getVertex(int i) { assert(i >= 0 && i < vNum); return vertexs[i]; }
    
    // FOR EDITING OPERATIONS
    virtual void moveControlPoint(int selectedPoint, float x, float y) {
        assert(selectedPoint >= 0 && selectedPoint < vNum);
        vertexs[selectedPoint].Set(x, y, 0);
    }
    virtual void addControlPoint(int selectedPoint, float x, float y) { 
        vertexs.insert(vertexs.begin() + selectedPoint, Vec3f(x, y, 0));
        vNum++;
    }
    virtual void deleteControlPoint(int selectedPoint) { 
        assert(selectedPoint >= 0 && selectedPoint < vNum);
        vertexs.erase(vertexs.begin() + selectedPoint);
        vNum--;
    }

    // FOR GENERATING TRIANGLES
    virtual TriangleMesh* OutputTriangles(ArgParser *args) { }
protected:
    vector<Vec3f> vertexs;
    int vNum;
};
#endif