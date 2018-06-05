#ifndef CRAY_HPP_
#define CRAY_HPP_

#include <time.h>
#include <stdlib.h>
#include "../Cpoint.hpp"
#include "../Cvector.hpp"

class OBJTriangle;

class CRay{
private:
  //motion probabilities : straight line, parabolic curve, flowing
  float _ks, _kp, _kf;

  //Carrier attributes : humidity, amount of dirt, amount of fungus
  float _sh, _sd, _sf;

  //position
  Cpoint origin;
  
  //---direction
  Cvector direction;

  int id;

public:
  CRay();
  CRay(float ks, float kp, float kf,
       float sh, float sd, float sf,
       Cpoint p, Cvector v, int id);
  
  float getStraightLine() const;
  float getParabolicCurve() const;
  float getFlowing() const;
  
  float getHumidity() const;
  float getAmountDirt() const;
  float getAmountFungus() const;

  //------
  Cpoint getOrigin() const;

  Cvector getDirection() const;

  int getId() const;
  
  void postHit(OBJTriangle surface);
  
};

#endif
