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

   origin_ray = Ray;
}

void CIntersection::drawSceneIntersection(){
	glBegin(GL_POINTS);
	glColor3f(0.5,0.5,1);
	glVertex3f(getInterX(), getInterY(), getInterZ());
	glEnd();
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

CRay CIntersection::getOriginRay() const{
  return origin_ray;
}

float CIntersection::getDistFromOri() const{
  return distance;
}
