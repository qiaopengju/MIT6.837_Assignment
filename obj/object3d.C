#include "object3d.h"
#include "grid.h"

void Object3D::insertIntoGrid(Grid *g, Matrix *m) {
    if (g == NULL) return;
    int nx = g->getNx();
    int ny = g->getNy();
    int nz = g->getNz();
    if (m) boundingBox->Transform(m);
    Vec3f minIdx, maxIdx;
    g->getCellIndex(minIdx, boundingBox->getMin());
    g->getCellIndex(maxIdx, boundingBox->getMax());
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (i >= minIdx.x() && i <= maxIdx.x() &&
                    j >= minIdx.y() && j <= maxIdx.y() && 
                    k >= minIdx.z() && k <= maxIdx.z())
                g->setCellOpaque(i, j, k, this);
            }
        }
    }
}