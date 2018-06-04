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
   cout << "Ray.getOrigin().getY() : " << Ray.getOrigin().getY() << endl;
   cout << "Ray.getDirection().getY() : " << Ray.getDirection().getY() << endl;
   cout << "NT : " << nT << endl;
   z=Ray.getOrigin().getZ() + (Ray.getDirection().getZ() * nT);
   cout << "X = " << x << endl;
   cout << "Y = " << y << endl;
   cout << "Z = " << z << endl;
   objet=Facet;
   alpha=nalpha;
   beta=nbeta;
}

void CIntersection::drawSceneIntersection(){
  cout << "DESSINER BOULE !!!" << endl;
  glutSolidSphere( 0.05, 20.0, 20.0); 
}

double CIntersection::getInterX() const{
  return x;
}

double CIntersection::getInterY() const{
  return y;
}

double CIntersection::getInterZ() const{
  return z;
}
