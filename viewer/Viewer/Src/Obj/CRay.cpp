#include "CRay.hpp"

#include "OBJTriangle.hpp"
CRay::CRay(){
  _ks = 0;
  _kp = 0;
  _kf = 0;
  
  _sh = 0;
  _sd = 0;
  _sf = 0;
}

CRay::CRay(float ks, float kp, float kf,
	   float sh, float sd, float sf,
	   Cpoint p, Cvector v, int id_cray){
  _ks = ks;
  _kp = kp;
  _kf = kf;
  
  _sh = sh;
  _sd = sd;
  _sf = sf;

  origin = p;
  direction = v;

  id = id_cray;
  
}

float CRay::getStraightLine() const{
  return _ks;
}
float CRay::getParabolicCurve() const{
  return _kp;
}
float CRay::getFlowing() const{
  return _kf;
}
  
float CRay::getHumidity() const{
  return _sh;
}
float CRay::getAmountDirt() const{
  return _sd;
}
float CRay::getAmountFungus() const{
  return _sf;
}

Cpoint CRay::getOrigin() const{
  return origin;
}

Cvector CRay::getDirection() const{
  return direction;
}

int CRay::getId() const{
  return id;
}

void CRay::postHit(OBJTriangle surface){
  float epsilon = (float) rand()/ RAND_MAX;
  if(epsilon < getStraightLine()){
  }
  else{
    if(epsilon < getParabolicCurve()){
    }
    else{
      if(epsilon < getFlowing()){
	
      }
      else{
	
      }
    }
  }
}
