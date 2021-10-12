#include <GL/glut.h>
#include "material.h"
#include "glCanvas.h"  

PhongMaterial::PhongMaterial(const Vec3f &diffuseColor, 
        const Vec3f &specularColor, float exponent){
    this->diffuseColor = diffuseColor;
    this->specularColor = specularColor;
    this->exponent = exponent;
}

void PhongMaterial::glSetMaterial() const {
  GLfloat one[4] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat zero[4] = { 0.0, 0.0, 0.0, 0.0 };
  GLfloat specular[4] = {
    getSpecularColor().r(),
    getSpecularColor().g(),
    getSpecularColor().b(),
    1.0};
  GLfloat diffuse[4] = {
    getDiffuseColor().r(),
    getDiffuseColor().g(),
    getDiffuseColor().b(),
    1.0};
  
  // NOTE: GL uses the Blinn Torrance version of Phong...      
  float glexponent = exponent;
  if (glexponent < 0) glexponent = 0;
  if (glexponent > 128) glexponent = 128;
  
#if !SPECULAR_FIX 
    
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &glexponent);
  
#else

  // OPTIONAL: 3 pass rendering to fix the specular highlight 
  // artifact for small specular exponents (wide specular lobe)

  if (SPECULAR_FIX_WHICH_PASS == 0) {
    // First pass, draw only the specular highlights
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &glexponent);
    
  } else if (SPECULAR_FIX_WHICH_PASS == 1) {
    // Second pass, compute normal dot light 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, one);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
  } else {
    // Third pass, add ambient & diffuse terms
    assert (SPECULAR_FIX_WHICH_PASS == 2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
  }
#endif
}

Vec3f PhongMaterial::Shade (const Ray &ray, const Hit &hit, 
    const Vec3f &_dirToLight, const Vec3f &lightColor) const{
  Vec3f dirToLight = _dirToLight;
  Vec3f norNormal = hit.getNormal();
  dirToLight.Normalize();
  norNormal.Normalize();

  //caculate diffuse color
  float diffuse = dirToLight.Dot3(norNormal);
  if (diffuse < 0) diffuse = 0; //点积为负，光在物体背面
  Vec3f diffuse_color = diffuse * getDiffuseColor() * lightColor;
  
  //caculate specular color
  Vec3f half_v = dirToLight - ray.getDirection(); //半程向量
  half_v.Normalize(); //一定要标准化半程向量
  float specular = half_v.Dot3(norNormal);
  if (specular < 0) specular = 0;
  specular = pow(specular, (float)exponent);
  Vec3f specular_color = specular * getSpecularColor() * lightColor;

  return diffuse_color + specular_color;
}