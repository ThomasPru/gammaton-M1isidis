#include "OBJTriangle.hpp"
#include "OBJReader.hpp"
#include "CIntersection.hpp"
#include <cmath>

OBJTriangle::OBJTriangle(){
  for(int i=0; i<3; i++){
    point[i].setCoordinate(-1);
    point[i].setNormal(-1);
    point[i].setTexture(-1);
  }
}

OBJTriangle::OBJTriangle(Surf surfac){
  for(int i=0; i<3; i++){
    point[i].setCoordinate(-1);
    point[i].setNormal(-1);
    point[i].setTexture(-1);
  }
  
  surface = surfac;
}

Surf OBJTriangle::getSurface() const{
  return surface;
}


void OBJTriangle::setVertices(int i, int j, int k){
  point[0].setCoordinate(i);
  point[1].setCoordinate(j);
  point[2].setCoordinate(k);
}

void OBJTriangle::setNormals(int i, int j, int k){
  point[0].setNormal(i);
  point[1].setNormal(j);
  point[2].setNormal(k);
}

void OBJTriangle::setTextures(int i, int j, int k){
  point[0].setTexture(i);
  point[1].setTexture(j);
  point[2].setTexture(k);
}



OBJVertex OBJTriangle::getVertex(int i){
  return point[i];
}


ostream& operator<<(ostream& out, const OBJTriangle& t){
  out << "f ";
  for(int i=0; i<3; i++)
    out << t.point[i].getCoordinate() << "/" << t.point[i].getTexture() << "/" << t.point[i].getNormal() << " ";
  out << endl;
  return out;
}





bool OBJTriangle::getIntersectionWithRay(const CRay& incidentRay, CIntersection &I)
{
   double det,inv_det;
   double u,v,t;

   /* find vectors for two edges sharing vert0 */
   Cvector edge1(r.getPointListInd(point[0].getCoordinate()), r.getPointListInd(point[1].getCoordinate()));
   Cvector edge2(r.getPointListInd(point[0].getCoordinate()), r.getPointListInd(point[2].getCoordinate()));

   /* begin calculating determinant - also used to calculate U parameter */
   Cvector pvec(incidentRay.getDirection()^edge2);// Cross product

   /* if determinant is near zero, ray lies in plane of triangle */
   det = edge1*pvec; // dot product
   if (det < MOLLEREPSILON) return false;

   /* calculate distance from vert0 to ray origin */
   Cvector tvec(r.getPointListInd(point[0].getCoordinate()),incidentRay.getOrigin());

   /* calculate U parameter and test bounds */
   u = tvec*pvec; // dot product
   if ((u < 0.0) || (u > det)) return false;

   /* prepare to test V parameter */
   Cvector qvec(tvec^edge1); // cross product

   /* calculate V parameter and test bounds */
   v = incidentRay.getDirection()*qvec; // dot product
   if ((v < 0.0) || ((u + v) > det)) return false;

   /* calculate t, scale parameters, ray intersects triangle */
   t = edge2*qvec; // dot product
   inv_det = 1.0 / det;

   t *= inv_det;
   u *= inv_det;
   v *= inv_det;
   

   t=sqrt(t*t);
   I.setPosition(t,incidentRay,this,u,v);

   return true;
}


