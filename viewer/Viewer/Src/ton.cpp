#include "ton.hpp"

ton::ton(float ks, float kp, float kf, float sh, float sd, float sf){
  _ks = ks;
  _kp = kp;
  _kf = kf;
  
  _sh = sh;
  _sd = sd;
  _sf = sf;
}

float ton::getStraightLine(){
  return _ks;
}
float ton::getParabolicCurve(){
  return _kp;
}
float ton::getFlowing(){
  return _kf;
}
  
float ton::getHumidity(){
  return _sh;
}
float ton::getAmountDirt(){
  return _sd;
}
float ton::getAmountFungus(){
  return _sf;
}
