#include "CRay.hpp"

CRay::CRay(){
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
