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

  // SHADE
  virtual Vec3f Shade (const Ray &ray, const Hit &hit, 
      const Vec3f &dirToLight, const Vec3f &lightColor) const = 0;
  // GL Set Material
  virtual void glSetMaterial() const {};
  // ACCESSORS
  virtual Vec3f getDiffuseColor() const { return diffuseColor; }
  virtual Vec3f getSpecularColor() const = 0;
  virtual Vec3f getReflectiveColor() const = 0;
  virtual Vec3f getTransparentColor() const = 0;
  virtual float getIndexOfRefraction() const = 0;

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
      const Vec3f &specularColor=Vec3f(0,0,0), float exponent=0);
  PhongMaterial(const Vec3f &diffuseColor, 
      const Vec3f &specularColor, float exponent, 
      const Vec3f &reflectiveColor, const Vec3f &transparentColor, float indexOfRefraction); 
  // ACCESSOR
  Vec3f getSpecularColor() const { return specularColor; };
  Vec3f getReflectiveColor() const { return reflectiveColor; }
  Vec3f getTransparentColor() const { return transparentColor; }
  float getIndexOfRefraction() const { return indexOfRefraction; }

  void glSetMaterial() const;
  Vec3f Shade (const Ray &ray, const Hit &hit, 
      const Vec3f &dirToLight, const Vec3f &lightColor) const;
protected:
  Vec3f specularColor, reflectiveColor, transparentColor;
  float exponent, indexOfRefraction;
};

// ====================================================================
// CheckerBoard Material
// ====================================================================
class CheckerBoard : public Material{
public:
  CheckerBoard(Matrix *m, Material *mat1, Material *mat2);
  void glSetMaterial() const;
  Vec3f Shade (const Ray &ray, const Hit &hit, 
      const Vec3f &dirToLight, const Vec3f &lightColor) const;
  Vec3f getSpecularColor() const { };
  Vec3f getReflectiveColor() const { };
  Vec3f getTransparentColor() const { };
  float getIndexOfRefraction() const { };
private:
  Material *mat1, *mat2;
  Matrix *matrix;
};

#endif
