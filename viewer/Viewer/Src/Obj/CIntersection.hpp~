#ifndef CINTERSECTION_HPP_
#define CINTERSECTION_HPP_

#include "../Cpoint.hpp"
#include "OBJMaterial.hpp"
#include "OBJTriangle.hpp"

class CIntersection : public Cpoint{
private:
  OBJTriangle *objet;// objet sur lequel se situe l’intersection
  float distance;// distance param ́etrique par rapport `a l’origine du rayon

  double alpha;
  double beta;
  
public:
  CIntersection();
  CIntersection(const Cpoint& p, OBJTriangle* o, const float& t);
  ~CIntersection(){}; // ne pas effacer objet !!!

  void setPosition(const double& nT,  const CRay& Ray, OBJTriangle *Facet,
	      const double& nalpha, const double& nbeta);
};

#endif
