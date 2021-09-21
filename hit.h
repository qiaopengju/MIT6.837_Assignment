#ifndef _HIT_H
#define _HIT_H

#include "vectors.h"
#include "ray.h"

class Material;

// ====================================================================
// ====================================================================

class Hit {
  
public:

  // CONSTRUCTOR & DESTRUCTOR
  Hit() { material = NULL; }
  Hit(float _t, Material *m) { 
    t = _t; material = m; }
  Hit(float _t, Material *m, Vec3f n): t(_t), material(m), normal(n) {} //add from Assignment2
  Hit(const Hit &h) { 
    t = h.t; 
    material = h.material; 
    intersectionPoint = h.intersectionPoint; 
    normal = h.normal;
  }
  ~Hit() {}

  // ACCESSORS
  float getT() const { return t; }
  Material* getMaterial() const { return material; }
  Vec3f getIntersectionPoint() const { return intersectionPoint; }
  Vec3f getNormal() const { return normal; } //add from Assignment2
  
  // MODIFIER
  void set(float _t, Material *m, const Ray &ray) {
    t = _t; material = m; 
    intersectionPoint = ray.pointAtParameter(t); }
  void set(float _t, Material *m, Vec3f n, const Ray &ray){ 
    t = _t; material = m; normal = n;
    intersectionPoint = ray.pointAtParameter(t);
  }

private: 

  // REPRESENTATION
  float t;
  Material *material;
  Vec3f intersectionPoint;
  Vec3f normal; //add from Assignment2

};

inline ostream &operator<<(ostream &os, const Hit &h) {
  os << "Hit <t:" << h.getT() <<">";
  return os;
}
// ====================================================================
// ====================================================================

#endif
