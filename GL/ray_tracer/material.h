#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vectors.h"
// include glCanvas.h to access the preprocessor variable SPECULAR_FIX
#include "ray.h"
#include "hit.h"
  #ifdef SPECULAR_FIX
// OPTIONAL:  global variable allows (hacky) communication 
// with glCanvas::display
extern int SPECULAR_FIX_WHICH_PASS;
  #endif

// ====================================================================
// ====================================================================

// You will extend this class in later assignments

class Material {

public:
  // CONSTRUCTORS & DESTRUCTOR
  Material()=default;
  Material(const Vec3f &d_color) { diffuseColor = d_color; }
  ~Material() {}

  // ACCESSORS
  virtual Vec3f getDiffuseColor() const { return diffuseColor; }
  // SHADE
  virtual Vec3f Shade (const Ray &ray, const Hit &hit, 
      const Vec3f &dirToLight, const Vec3f &lightColor) const = 0;
  // GL Set Material
  virtual void glSetMaterial() const {};

protected:

  // REPRESENTATION
  Vec3f diffuseColor;
  
};

// ====================================================================
// Phong Lighting Material
// ====================================================================
class PhongMaterial : public Material{
public:
  //CONSTURCTURS
  PhongMaterial(const Vec3f &diffuseColor, 
     const Vec3f &specularColor, float exponent);
  // ACCESSOR
  Vec3f getSpecularColor() const { return specularColor; };
  void glSetMaterial() const;
  Vec3f Shade (const Ray &ray, const Hit &hit, 
      const Vec3f &dirToLight, const Vec3f &lightColor) const;
protected:
  Vec3f specularColor;
  float exponent;
};
#endif
