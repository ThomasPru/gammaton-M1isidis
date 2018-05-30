#include "CIntersection.hpp"

CIntersection::CIntersection(){
}

CIntersection::CIntersection(const Cpoint& p, OBJTriangle* o, const float& t){
  objet = o;
  distance = t;
}

void CIntersection::setPosition(const double& nT,
                 const CRay& Ray,
                 OBJTriangle *Facet,
                 const double& nalpha,
                 const double& nbeta)
{
   distance=nT;
   x=Ray.getOrigin().getX() + (Ray.getDirection().getX() * nT);
   y=Ray.getOrigin().getY() + (Ray.getDirection().getY() * nT);
   z=Ray.getOrigin().getZ() + (Ray.getDirection().getZ() * nT);
   objet=Facet;
   alpha=nalpha;
   beta=nbeta;
}