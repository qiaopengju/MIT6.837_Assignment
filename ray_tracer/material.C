#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include "material.h"
#include "glCanvas.h"  
#include "raytracer.h"

PhongMaterial::PhongMaterial(const Vec3f &diffuseColor, 
    const Vec3f &specularColor, float exponent){
  this->diffuseColor = diffuseColor;
  this->specularColor = specularColor;
  this->exponent = exponent;
  reflectiveColor = Vec3f(0,0,0);
  transparentColor = Vec3f(0,0,0);
  indexOfRefraction = 1; //默认空气折射率1
}

PhongMaterial::PhongMaterial(const Vec3f &diffuseColor, 
    const Vec3f &specularColor, float exponent, 
    const Vec3f &reflectiveColor, const Vec3f &transparentColor, float indexOfRefraction){
  this->diffuseColor = diffuseColor;
  this->specularColor = specularColor;
  this->exponent = exponent;
  this->reflectiveColor = reflectiveColor;
  this->transparentColor = transparentColor;
  this->indexOfRefraction = indexOfRefraction;
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

// return specular & diffuse color
Vec3f PhongMaterial::Shade (const Ray &ray, const Hit &hit, 
    const Vec3f &_dirToLight, const Vec3f &lightColor) const{
  Vec3f dirToLight = _dirToLight;
  Vec3f norNormal = hit.getNormal();
  //Vec3f norRayDir = ray.getDirection();
  dirToLight.Normalize();
  norNormal.Normalize();
  //norRayDir.Normalize();

  //caculate diffuse color
  if (shade_back && dirToLight.Dot3(norNormal) < 0) norNormal = -1 * norNormal;
  float diffuse = dirToLight.Dot3(norNormal);
  //if (shade_back) diffuse = abs(diffuse);
  if (diffuse < 0) diffuse = 0; //点积为负，光在物体背面
  Vec3f diffuse_color = diffuse * getDiffuseColor() * lightColor;
  
  //caculate specular color
  Vec3f half_v = dirToLight - ray.getDirection(); //半程向量
  half_v.Normalize(); //一定要标准化半程向量
  float specular = half_v.Dot3(norNormal);
  //if (dirToLight.Dot3(norNormal) < 0) specular *= diffuse; //背面不应该有高光
  specular *= diffuse;  //背面不应该有高光反射 & 柔化阴影边缘

  specular = powf(specular, exponent);
  Vec3f specular_color = specular * getSpecularColor() * lightColor;

  return diffuse_color + specular_color;
}

void CheckerBoard::glSetMaterial() const{
  mat1->glSetMaterial();
}

Vec3f CheckerBoard::Shade(const Ray &ray, const Hit &hit, 
    const Vec3f &dirToLight, const Vec3f &lightColor) const{
}