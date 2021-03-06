#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include "material.h"
#include "glCanvas.h"  
#include "raytracer.h"
#include "texture/perlin_noise.h"
#define odd(x) (x % 2 == 1)

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
  if (dirToLight.Dot3(norNormal) < 0) specular *= diffuse; //背面不应该有高光
  // specular *= diffuse;  //背面不应该有高光反射 & 柔化阴影边缘

  specular = powf(specular, exponent);
  Vec3f specular_color = specular * getSpecularColor() * lightColor;

  return diffuse_color + specular_color;
}

CheckerBoard::CheckerBoard(Matrix *m, Material *mat1, Material *mat2){
  matrix = m;
  this->mat1 = mat1;
  this->mat2 = mat2;
}

void CheckerBoard::glSetMaterial() const{
  mat1->glSetMaterial();
}

Vec3f CheckerBoard::Shade(const Ray &ray, const Hit &hit, 
    const Vec3f &dirToLight, const Vec3f &lightColor) const{
  Vec3f hitPos = hit.getIntersectionPoint();
  matrix->Transform(hitPos);
  hitPos.Set(floor(hitPos.x()), floor(hitPos.y()), floor(hitPos.z()));
  hitPos.Set(abs(hitPos.x()), abs(hitPos.y()), abs(hitPos.z()));
  if (odd((int)hitPos.y())){
    if (odd((int)hitPos.z())){
      if (odd((int)hitPos.x())) return mat1->Shade(ray, hit, dirToLight, lightColor);
      else return mat2->Shade(ray, hit, dirToLight, lightColor);
    } else {
      if (!odd((int)hitPos.x())) return mat1->Shade(ray, hit, dirToLight, lightColor);
      else return mat2->Shade(ray, hit, dirToLight, lightColor);
    }
  } else{
    if (odd((int)hitPos.z())){
      if (!odd((int)hitPos.x())) return mat1->Shade(ray, hit, dirToLight, lightColor);
      else return mat2->Shade(ray, hit, dirToLight, lightColor);
    } else {
      if (odd((int)hitPos.x())) return mat1->Shade(ray, hit, dirToLight, lightColor);
      else return mat2->Shade(ray, hit, dirToLight, lightColor);
    }
  }
}

Noise::Noise(Matrix *m, Material *mat1, Material *mat2, int octaves){
  matrix = m;
  this->mat1 = mat1;
  this->mat2 = mat2;
  this->octaves = octaves;
}

void Noise::glSetMaterial() const{
  mat1->glSetMaterial();
}

Vec3f Noise::getDiffuseColor(Vec3f wordPos) const {
  matrix->Transform(wordPos);
  float noise(0);
  for (float i = 1; i <= octaves; i++)
    noise += PerlinNoise::noise(i * wordPos.x(), i * wordPos.y(), i * wordPos.z()) / i;
  noise = (noise + 1) / 2;
  return noise * mat1->getDiffuseColor() + (1 - noise) * mat2->getDiffuseColor();
}

Vec3f Noise::Shade(const Ray &ray, const Hit &hit, 
    const Vec3f &dirToLight, const Vec3f &lightColor) const{
  Vec3f hitPos = hit.getIntersectionPoint();
  matrix->Transform(hitPos);
  //calculate noise
  float noise(0);
  for (float i = 1; i <= octaves; i++)
    noise += PerlinNoise::noise(i * hitPos.x(), i * hitPos.y(), i * hitPos.z()) / i;
  noise = (noise + 1) / 2;
  //return color by noise
  return noise * mat1->Shade(ray, hit, dirToLight, lightColor) + 
    (1 - noise) * mat2->Shade(ray, hit, dirToLight, lightColor);
}

Marble::Marble(Matrix *m, Material *mat1, Material *mat2, int octaves, float frequency, float amplitude){
  matrix = m;
  this->mat1 = mat1;
  this->mat2 = mat2;
  this->octaves = octaves;
  this->frequency = frequency;
  this->amplitude = amplitude;
}

void Marble::glSetMaterial() const{
  mat1->glSetMaterial();
}

Vec3f Marble::getDiffuseColor(Vec3f wordPos) const {
  matrix->Transform(wordPos);
  float noise(0);
  for (float i = 1; i <= octaves; i++)
    noise += PerlinNoise::noise(i * wordPos.x(), i * wordPos.y(), i * wordPos.z()) / i;
  noise = (noise + 1) / 2;
  float marble = sin(frequency * wordPos.x() + amplitude * noise);
  marble = (marble + 1) / 2;
  return marble * mat1->getDiffuseColor() + (1 - marble) * mat2->getDiffuseColor();
}

//大理石纹理
Vec3f Marble::Shade(const Ray &ray, const Hit &hit, 
    const Vec3f &dirToLight, const Vec3f &lightColor) const{
  Vec3f hitPos = hit.getIntersectionPoint();
  matrix->Transform(hitPos);
  //calculate marble
  float noise(0);
  for (float i = 1; i <= octaves; i++)
    noise += PerlinNoise::noise(i * hitPos.x(), i * hitPos.y(), i * hitPos.z()) / i;
  noise = (noise + 1) / 2;
  float marble = sin(frequency * hitPos.x() + amplitude * noise);
  marble = (marble + 1) / 2;
  //return color by marble
  return marble * mat1->Shade(ray, hit, dirToLight, lightColor) + 
    (1 - marble) * mat2->Shade(ray, hit, dirToLight, lightColor);
}

Wood::Wood(Matrix *m, Material *mat1, Material *mat2, int octaves, float frequency, float amplitude){
  matrix = m;
  this->mat1 = mat1;
  this->mat2 = mat2;
  this->octaves = octaves;
  this->frequency = frequency;
  this->amplitude = amplitude;
}

void Wood::glSetMaterial() const{
  mat1->glSetMaterial();
}

Vec3f Wood::getDiffuseColor(Vec3f wordPos) const {
  matrix->Transform(wordPos);
  float noise(0);
  for (float i = 1; i <= octaves; i++)
    noise += PerlinNoise::noise(i * wordPos.x(), i * wordPos.y(), i * wordPos.z()) / i;
  noise = (noise + 1) / 2;
  float r2 = (pow(wordPos.x(), 2) + pow(wordPos.y(), 2) + pow(wordPos.z(), 2)) / 10;
  float wood = sin(frequency * r2 + amplitude * noise * 2);
  wood = (wood + 1) / 2;
  return wood * mat1->getDiffuseColor() + (1 - wood) * mat2->getDiffuseColor();
}

Vec3f Wood::Shade(const Ray &ray, const Hit &hit, 
    const Vec3f &dirToLight, const Vec3f &lightColor) const{
  Vec3f hitPos = hit.getIntersectionPoint();
  matrix->Transform(hitPos);
  //calculate marble
  float noise(0);
  for (float i = 1; i <= octaves; i++)
    noise += PerlinNoise::noise(i * hitPos.x(), i * hitPos.y(), i * hitPos.z()) / i;
  noise = (noise + 1) / 2;
  float r2 = pow(hitPos.x(), 2) + pow(hitPos.y(), 2) * 0.3 + pow(hitPos.z(), 2);
  float wood = sin(frequency * r2 + amplitude * noise * 2);
  wood = (wood + 1) / 2;
  //return color by marble
  return wood * mat1->Shade(ray, hit, dirToLight, lightColor) + 
    (1 - wood) * mat2->Shade(ray, hit, dirToLight, lightColor);
}