#ifndef MACHINGINFO_H
#define MACHINGINFO_H

#include "vectors.h"

namespace Sign{
    enum sign{positive=1, negative=-1};
}

class MarchingInfo{
public:
    MarchingInfo() = default;

    //3DDDA
    //choose the smallest of the next t values (t_next_x, t_next_y, and t_next_z), and updates the corresponding cell index
    bool nextCell(){
        float t_minNext = min2(min2(t_nextX, t_nextY), t_nextZ);
        if (t_minNext == t_nextX){
            indexI += sign_x;
            tmin = t_nextX;
            t_nextX += d_tx;
            if (indexI < 0 || indexI >= nx) return false;
            surfaceNormal.Set(-sign_x, 0, 0);
        } else if (t_minNext == t_nextY){
            indexJ += sign_y;
            tmin = t_nextY;
            t_nextY += d_ty;
            if (indexJ < 0 || indexJ >= ny) return false;
            surfaceNormal.Set(0, -sign_y, 0);
        } else{
            indexK += sign_z;
            tmin = t_nextZ;
            t_nextZ += d_tz;
            if (indexK < 0 || indexK >= nz) return false;
            surfaceNormal.Set(0, 0, -sign_z);
        }
        return true;
    }

    //Modify
    void setIndex(float x, float y, float z){ setIndex(Vec3f(x, y, z)); }
    void setIndex(Vec3f index){
        indexI = index.x();
        indexJ = index.y();
        indexK = index.z();
    }
    void setGridSize(int _nx, int _ny, int _nz){
        nx = _nx;
        ny = _ny;
        nz = _nz;
    }

    //current value of tmin
    float tmin;
    //The next values of intersection along each axis
    float t_nextX, t_nextY, t_nextZ;
    //The marching increments along each axis
    float d_tx, d_ty, d_tz;
    //The sign of the direction vector components
    Sign::sign sign_x, sign_y, sign_z;
    //The grid indices i, j, and k for the current grid cell
    int indexI, indexJ, indexK;
    //The surface normal of the cell face which was crossed to enter the current cell
    Vec3f surfaceNormal;
private:
    //grid
    int nx, ny, nz;
};

#endif