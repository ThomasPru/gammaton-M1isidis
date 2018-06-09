#ifndef CINTERSECTION_HPP_
#define CINTERSECTION_HPP_

#include "../Cpoint.hpp"
#include "OBJMaterial.hpp"
#include "OBJTriangle.hpp"

//------------------------------
//---Ajouts
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
//------------------------------

class CIntersection : public Cpoint{
private:
  OBJTriangle *objet;// objet sur lequel se situe l’intersection
  float distance;// distance param ́etrique par rapport `a l’origine du rayon

  double alpha;
  double beta;

  double x;
  double y;
  double z;

  CRay origin_ray;
  
public:
  CIntersection();
  CIntersection(const Cpoint& p, OBJTriangle* o, const float& t);
  ~CIntersection(){}; // ne pas effacer objet !!!

  void setPosition(const double& nT, const CRay& Ray, OBJTriangle *Facet,
	      const double& nalpha, const double& nbeta);

  void drawSceneIntersection();

  double getInterX() const;
  double getInterY() const;
  double getInterZ() const;

  CRay getOriginRay() const;

  void postHit(CRay& ray);

  float getDistFromOri() const;
};

#endif
