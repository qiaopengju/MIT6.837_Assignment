#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include "boundingbox.h"

// ====================================================================
// ====================================================================
void BoundingBox::Transform(Matrix *m){
    //caculate bounding box
    float arrayX[8], arrayY[8], arrayZ[8];
    Vec3f v1(max.x(), min.y(), min.z()); m->Transform(v1); arrayX[0] = v1.x(); arrayY[0] = v1.y(); arrayZ[0] = v1.z();
    Vec3f v2(max.x(), max.y(), min.z()); m->Transform(v2); arrayX[1] = v2.x(); arrayY[1] = v2.y(); arrayZ[1] = v2.z();
    Vec3f v3(min.x(), max.y(), min.z()); m->Transform(v3); arrayX[2] = v3.x(); arrayY[2] = v3.y(); arrayZ[2] = v3.z();
    Vec3f v4(min.x(), min.y(), min.z()); m->Transform(v4); arrayX[3] = v4.x(); arrayY[3] = v4.y(); arrayZ[3] = v4.z();
    Vec3f v5(max.x(), min.y(), max.z()); m->Transform(v5); arrayX[4] = v5.x(); arrayY[4] = v5.y(); arrayZ[4] = v5.z();
    Vec3f v6(max.x(), max.y(), max.z()); m->Transform(v6); arrayX[5] = v6.x(); arrayY[5] = v6.y(); arrayZ[5] = v6.z();
    Vec3f v7(min.x(), max.y(), max.z()); m->Transform(v7); arrayX[6] = v7.x(); arrayY[6] = v7.y(); arrayZ[6] = v7.z();
    Vec3f v8(min.x(), min.y(), max.z()); m->Transform(v8); arrayX[7] = v8.x(); arrayY[7] = v8.y(); arrayZ[7] = v8.z();
    sort(arrayX, arrayX+8);
    sort(arrayY, arrayY+8);
    sort(arrayZ, arrayZ+8);
    *this = BoundingBox(Vec3f(arrayX[0], arrayY[0], arrayZ[0]), Vec3f(arrayX[7], arrayY[7], arrayZ[7]));
}

void BoundingBox::paint() const {
  // draw a wireframe box to represent the boundingbox
  
  glColor3f(1,1,1);
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);

  glVertex3f(min.x(),min.y(),min.z());
  glVertex3f(max.x(),min.y(),min.z());
  glVertex3f(min.x(),min.y(),min.z());
  glVertex3f(min.x(),max.y(),min.z());
  glVertex3f(max.x(),max.y(),min.z());
  glVertex3f(max.x(),min.y(),min.z());
  glVertex3f(max.x(),max.y(),min.z());
  glVertex3f(min.x(),max.y(),min.z());

  glVertex3f(min.x(),min.y(),min.z());
  glVertex3f(min.x(),min.y(),max.z());
  glVertex3f(min.x(),max.y(),min.z());
  glVertex3f(min.x(),max.y(),max.z());
  glVertex3f(max.x(),min.y(),min.z());
  glVertex3f(max.x(),min.y(),max.z());
  glVertex3f(max.x(),max.y(),min.z());
  glVertex3f(max.x(),max.y(),max.z());

  glVertex3f(min.x(),min.y(),max.z());
  glVertex3f(max.x(),min.y(),max.z());
  glVertex3f(min.x(),min.y(),max.z());
  glVertex3f(min.x(),max.y(),max.z());
  glVertex3f(max.x(),max.y(),max.z());
  glVertex3f(max.x(),min.y(),max.z());
  glVertex3f(max.x(),max.y(),max.z());
  glVertex3f(min.x(),max.y(),max.z());

  glEnd();
  glEnable(GL_LIGHTING);	   
}

// ====================================================================
// ====================================================================
