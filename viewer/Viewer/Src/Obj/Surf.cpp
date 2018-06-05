#include "Surf.hpp"

Surf::Surf(){
  _sh = 0;
  _sd = 0;
  _sf = 0;

  //deterioration rate
  _ds = 0;
  _dp = 0;
  _sf = 0;
}


Surf::Surf(float sh, float sd, float sf, float ds, float dp, float df){
  _sh = sh;
  _sd = sd;
  _sf = sf;
  
  _ds = ds;
  _dp = dp;
  _df = df;
  
}
