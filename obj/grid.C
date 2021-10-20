#include "grid.h"
#include "marchingInfo.h"
#include "rayTree.h"

#define NMaterial 10
Vec3f v1, v2, v3, v4, v5, v6, v7, v8;

PhongMaterial materialList[NMaterial] = {
    PhongMaterial(Vec3f(1,1,1)), 
    PhongMaterial(Vec3f(0.7,1,1)), 
    PhongMaterial(Vec3f(0.3,1,1)), 
    PhongMaterial(Vec3f(0.3,0.7,1)), 
    PhongMaterial(Vec3f(0.3,0.3,1)), 
    PhongMaterial(Vec3f(0.3,0.3,0.7)), 
    PhongMaterial(Vec3f(0.7,0.3,0.3)), 
    PhongMaterial(Vec3f(0.3,0.7,0.3)), 
    PhongMaterial(Vec3f(0.3,0.7,0.7)), 
    PhongMaterial(Vec3f(0.7,0.7,0.3))};

Grid::Grid(BoundingBox *bb, int nx, int ny, int nz){
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
    boundingBox = bb;
    opaque = new Object3DVector[nx * ny * nz];
    material = new PhongMaterial(Vec3f(1,1,1), Vec3f(0,0,0), 0);
    //bounding Box
    boundingBox = bb;
    Vec3f max = boundingBox->getMax();
    min = boundingBox->getMin();
    if (nx) lenCellX = (max.x() - min.x()) / nx;
    if (ny) lenCellY = (max.y() - min.y()) / ny;
    if (nz) lenCellZ = (max.z() - min.z()) / nz;

    //min cell 的8个顶点坐标
    Vec3f cellMax = min + Vec3f(lenCellX, lenCellY, lenCellZ);
    v1.Set(min.x(), min.y(), cellMax.z());
    v2.Set(cellMax.x(), min.y(), cellMax.z());
    v3.Set(cellMax.x(), min.y(), min.z());
    v4.Set(min.x(), min.y(), min.z());
    v5.Set(min.x(), cellMax.y(), cellMax.z());
    v6.Set(cellMax.x(), cellMax.y(), cellMax.z());
    v7.Set(cellMax.x(), cellMax.y(), min.z());
    v8.Set(min.x(), cellMax.y(), min.z());
}

Grid::~Grid(){
    delete [] opaque;
}

//intersect grid boudingbox and ray
//hit.T is tmin, not hit point's T
bool Grid::intersect(const Ray &r, Hit &h, float tmin){
    MarchingInfo mInfo;
    this->initializeRayMarch(mInfo, r, tmin);
    for (int i = 0; true; i++){
        //intersect each primitive in cell
        int index = mInfo.indexI*ny*nz + mInfo.indexJ*nz +mInfo.indexK;
        if (opaque[index].getNumObjects() != 0){
            h.set(mInfo.tmin, material, r);
            //return true;
        }
        paintCellRayTree(mInfo.indexI, mInfo.indexJ, mInfo.indexK, &materialList[i%NMaterial]);
        if (!mInfo.nextCell()) break;
    }
    return false;
}

//get cell center pos, index begin from zero
void Grid::getCellPos(Vec3f &pos, const Vec3f &index){
    float x = min.x() + index.x() * lenCellX + lenCellX / 2;
    float y = min.y() + index.y() * lenCellY + lenCellY / 2;
    float z = min.z() + index.z() * lenCellZ + lenCellZ / 2;
    pos.Set(x, y, z);
}

void Grid::getCellPosMin(Vec3f &pos, const int &i, const int &j, const int &k){
    pos.Set(min.x() + i*lenCellX, min.y() + j*lenCellY, min.z() + k*lenCellZ);
}

void Grid::getCellIndex(Vec3f &index, const Vec3f &pos){
    float off_x = pos.x() - min.x();
    float off_y = pos.y() - min.y();
    float off_z = pos.z() - min.z();
    int i = floor(min2(nx-1, max2(0, off_x / lenCellX)));
    int j = floor(min2(ny-1, max2(0, off_y / lenCellX)));
    int k = floor(min2(nz-1, max2(0, off_z / lenCellX)));
    //int i = off_x / lenCellX));
    //int j = off_y / lenCellX));
    //int k = off_z / lenCellX));
    index.Set(i, j, k);
}

//computes the marching increments and the information for the first cell traversed by the ray
void Grid::initializeRayMarch(MarchingInfo &mi, const Ray &r, float tmin) {
    //init marching information
    mi.setGridSize(nx, ny, nz);
    Vec3f rDir = r.getDirection(); rDir.Normalize();
    Vec3f rOri = r.getOrigin();
    //must abs d_t!!!!
    mi.d_tx = fabs(lenCellX / rDir.x());
    mi.d_ty = fabs(lenCellY / rDir.y());
    mi.d_tz = fabs(lenCellZ / rDir.z());
    mi.sign_x = rDir.x() > 0 ? Sign::positive : Sign::negative;
    mi.sign_y = rDir.y() > 0 ? Sign::positive : Sign::negative;
    mi.sign_z = rDir.z() > 0 ? Sign::positive : Sign::negative;
    //mi.tmin = tmin;
    //ray - bounding box collision detection
    //init first cell
    float T = INFINITY;
    Vec3f max = boundingBox->getMax();
    float tx1 = rDir.x() > 0 ? (min.x()-rOri.x()) / rDir.x() : (max.x()-rOri.x()) / rDir.x();
    float tx2 = rDir.x() > 0 ? (max.x()-rOri.x()) / rDir.x() : (min.x()-rOri.x()) / rDir.x();
    float ty1 = rDir.y() > 0 ? (min.y()-rOri.y()) / rDir.y() : (max.y()-rOri.y()) / rDir.y();
    float ty2 = rDir.y() > 0 ? (max.y()-rOri.y()) / rDir.y() : (min.y()-rOri.y()) / rDir.y();
    float tz1 = rDir.z() > 0 ? (min.z()-rOri.z()) / rDir.z() : (max.z()-rOri.z()) / rDir.z();
    float tz2 = rDir.z() > 0 ? (max.z()-rOri.z()) / rDir.z() : (min.z()-rOri.z()) / rDir.z();
    float tEnter = max2(max2(tx1, ty1), tz1);
    float tExit = min2(min2(tx2, ty2), tz2);
    if (tEnter < tExit && tExit >= 0){ //hit!
        if (tEnter < 0) { //ray rOri is inside the box
            if (tExit >= tmin) T = tmin; 
        } else { //ray rOri outside
            if (tEnter >= tmin) T = tEnter; 
        }
    } 
    Vec3f hitPos = r.pointAtParameter(T);
#ifdef DEBUG
    printf("HIT POS: (%.3f, %.3f, %.3f)\n", hitPos.x(), hitPos.y(), hitPos.z());
#endif
    Vec3f hitIdx;   this->getCellIndex(hitIdx, hitPos);
    mi.setIndex(hitIdx);
    //caculate nextX,Y,Z
    int nIdxX = hitIdx.x() + mi.sign_x;
    int nIdxY = hitIdx.y() + mi.sign_y;
    int nIdxZ = hitIdx.z() + mi.sign_z;
    Vec3f nextMinPos; this->getCellPosMin(nextMinPos, nIdxX, nIdxY, nIdxZ);
    Vec3f nextMaxPos = nextMinPos + Vec3f(lenCellX, lenCellY, lenCellZ);
    mi.t_nextX = mi.sign_x == Sign::positive ? (nextMinPos.x()-rOri.x()) / rDir.x() : (nextMaxPos.x()-rOri.x()) / rDir.x();
    mi.t_nextY = mi.sign_y == Sign::positive ? (nextMinPos.y()-rOri.y()) / rDir.y() : (nextMaxPos.y()-rOri.y()) / rDir.y();
    mi.t_nextZ = mi.sign_z == Sign::positive ? (nextMinPos.z()-rOri.z()) / rDir.z() : (nextMaxPos.z()-rOri.z()) / rDir.z();
}

// The paint routine is responsible for
// making the OpenGL calls to draw the object to the screen.
void Grid::paint(void){
    //min max is unit cell size
    //material->glSetMaterial();
    Vec3f normal;
    Material *m;
    glBegin(GL_QUADS);
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                float sx = i * lenCellX;
                float sy = j * lenCellY;
                float sz = k * lenCellZ;

                switch (opaque[i*ny*nz + j*nz + k].getNumObjects()) {
                    case 1: m = new PhongMaterial(Vec3f(1, 1, 1)); break;
                    case 2: m = new PhongMaterial(Vec3f(1, 0, 1)); break;
                    case 3: m = new PhongMaterial(Vec3f(0, 1, 1)); break;
                    case 4: m = new PhongMaterial(Vec3f(1, 1, 0)); break;
                    case 5: m = new PhongMaterial(Vec3f(0.3, 0, 0.7)); break;
                    case 6: m = new PhongMaterial(Vec3f(0.7, 0, 0.3)); break;
                    case 7: m = new PhongMaterial(Vec3f(0, 0.3, 0.7)); break;
                    case 8: m = new PhongMaterial(Vec3f(0, 0.7, 0.3)); break;
                    case 9: m = new PhongMaterial(Vec3f(0, 0.3, 0.7)); break;
                    case 10: m = new PhongMaterial(Vec3f(0, 0.7, 0.3)); break;
                    case 11: m = new PhongMaterial(Vec3f(0, 1, 0)); break;
                    case 12: m = new PhongMaterial(Vec3f(0, 0, 1)); break;
                    case 13: m = new PhongMaterial(Vec3f(0.7, 1, 0)); break;
                    case 14: m = new PhongMaterial(Vec3f(0, 0.7, 1)); break;
                    case 15: m = new PhongMaterial(Vec3f(0, 1, 0.7)); break;
                    case 16: m = new PhongMaterial(Vec3f(0, 0.7, 1)); break;
                    case 17: m = new PhongMaterial(Vec3f(0.3, 0.5, 0.7)); break;
                    case 18: m = new PhongMaterial(Vec3f(0.7, 0.7, 1)); break;
                    case 19: m = new PhongMaterial(Vec3f(1, 0.5, 0.7)); break;
                    case 20: m = new PhongMaterial(Vec3f(1, 0.3, 0.3)); break;
                    default: m = new PhongMaterial(Vec3f(1, 0, 0)); break;
                }
                if (opaque[i*ny*nz + j*nz +k].getNumObjects() != 0){
                    //bottom
                    m->glSetMaterial();
                    Vec3f::Cross3(normal, v1-v2, v3-v2);
                    glNormal3f(normal.x(), normal.y(), normal.z());
                    glVertex3f(v4.x()+sx, v4.y()+sy, v4.z()+sz);
                    glVertex3f(v3.x()+sx, v3.y()+sy, v3.z()+sz);
                    glVertex3f(v2.x()+sx, v2.y()+sy, v2.z()+sz);
                    glVertex3f(v1.x()+sx, v1.y()+sy, v1.z()+sz);
                    //top
                    Vec3f::Cross3(normal, v5-v6, v7-v6);
                    glNormal3f(normal.x(), normal.y(), normal.z());
                    glVertex3f(v8.x()+sx, v8.y()+sy, v8.z()+sz);
                    glVertex3f(v7.x()+sx, v7.y()+sy, v7.z()+sz);
                    glVertex3f(v6.x()+sx, v6.y()+sy, v6.z()+sz);
                    glVertex3f(v5.x()+sx, v5.y()+sy, v5.z()+sz);
                    //left
                    Vec3f::Cross3(normal, v5-v1, v4-v1);
                    glNormal3f(normal.x(), normal.y(), normal.z());
                    glVertex3f(v5.x()+sx, v5.y()+sy, v5.z()+sz);
                    glVertex3f(v8.x()+sx, v8.y()+sy, v8.z()+sz);
                    glVertex3f(v4.x()+sx, v4.y()+sy, v4.z()+sz);
                    glVertex3f(v1.x()+sx, v1.y()+sy, v1.z()+sz);
                    //right
                    Vec3f::Cross3(normal, v3-v2, v6-v2);
                    glNormal3f(normal.x(), normal.y(), normal.z());
                    glVertex3f(v2.x()+sx, v2.y()+sy, v2.z()+sz);
                    glVertex3f(v3.x()+sx, v3.y()+sy, v3.z()+sz);
                    glVertex3f(v7.x()+sx, v7.y()+sy, v7.z()+sz);
                    glVertex3f(v6.x()+sx, v6.y()+sy, v6.z()+sz);
                    //front
                    Vec3f::Cross3(normal, v2-v1, v5-v1);
                    glNormal3f(normal.x(), normal.y(), normal.z());
                    glVertex3f(v1.x()+sx, v1.y()+sy, v1.z()+sz);
                    glVertex3f(v2.x()+sx, v2.y()+sy, v2.z()+sz);
                    glVertex3f(v6.x()+sx, v6.y()+sy, v6.z()+sz);
                    glVertex3f(v5.x()+sx, v5.y()+sy, v5.z()+sz);
                    //back
                    Vec3f::Cross3(normal, v8-v4, v3-v4);
                    glNormal3f(normal.x(), normal.y(), normal.z());
                    glVertex3f(v4.x()+sx, v4.y()+sy, v4.z()+sz);
                    glVertex3f(v8.x()+sx, v8.y()+sy, v8.z()+sz);
                    glVertex3f(v7.x()+sx, v7.y()+sy, v7.z()+sz);
                    glVertex3f(v3.x()+sx, v3.y()+sy, v3.z()+sz);
                }
            }
        }
    }
    glEnd();
}

void Grid::paintCellRayTree(Vec3f index, Material *m){
    index.Set((int)index.x(), (int)index.y(), (int)index.z());
    float sx = index.x() * lenCellX;
    float sy = index.y() * lenCellY;
    float sz = index.z() * lenCellZ;
    Vec3f normal, a, b, c, d;
    //bottom
    Vec3f::Cross3(normal, v1-v2, v3-v2);
    a.Set(v4.x()+sx, v4.y()+sy, v4.z()+sz);
    b.Set(v3.x()+sx, v3.y()+sy, v3.z()+sz);
    c.Set(v2.x()+sx, v2.y()+sy, v2.z()+sz);
    d.Set(v1.x()+sx, v1.y()+sy, v1.z()+sz);
    RayTree::AddHitCellFace(a, b, c, d, normal, m);
    //top
    Vec3f::Cross3(normal, v5-v6, v7-v6);
    a.Set(v8.x()+sx, v8.y()+sy, v8.z()+sz);
    b.Set(v7.x()+sx, v7.y()+sy, v7.z()+sz);
    c.Set(v6.x()+sx, v6.y()+sy, v6.z()+sz);
    d.Set(v5.x()+sx, v5.y()+sy, v5.z()+sz);
    RayTree::AddHitCellFace(a, b, c, d, normal, m);
    //left
    Vec3f::Cross3(normal, v5-v1, v4-v1);
    a.Set(v5.x()+sx, v5.y()+sy, v5.z()+sz);
    b.Set(v8.x()+sx, v8.y()+sy, v8.z()+sz);
    c.Set(v4.x()+sx, v4.y()+sy, v4.z()+sz);
    d.Set(v1.x()+sx, v1.y()+sy, v1.z()+sz);
    RayTree::AddHitCellFace(a, b, c, d, normal, m);
    //right
    Vec3f::Cross3(normal, v3-v2, v6-v2);
    a.Set(v2.x()+sx, v2.y()+sy, v2.z()+sz);
    b.Set(v3.x()+sx, v3.y()+sy, v3.z()+sz);
    c.Set(v7.x()+sx, v7.y()+sy, v7.z()+sz);
    d.Set(v6.x()+sx, v6.y()+sy, v6.z()+sz);
    RayTree::AddHitCellFace(a, b, c, d, normal, m);
    //front
    Vec3f::Cross3(normal, v2-v1, v5-v1);
    a.Set(v1.x()+sx, v1.y()+sy, v1.z()+sz);
    b.Set(v2.x()+sx, v2.y()+sy, v2.z()+sz);
    c.Set(v6.x()+sx, v6.y()+sy, v6.z()+sz);
    d.Set(v5.x()+sx, v5.y()+sy, v5.z()+sz);
    RayTree::AddHitCellFace(a, b, c, d, normal, m);
    //back
    Vec3f::Cross3(normal, v8-v4, v3-v4);
    a.Set(v4.x()+sx, v4.y()+sy, v4.z()+sz);
    b.Set(v8.x()+sx, v8.y()+sy, v8.z()+sz);
    c.Set(v7.x()+sx, v7.y()+sy, v7.z()+sz);
    d.Set(v3.x()+sx, v3.y()+sy, v3.z()+sz);
    RayTree::AddHitCellFace(a, b, c, d, normal, m);
}