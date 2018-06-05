#ifndef SURF_HPP_
#define SURF_HPP_

#include <iostream>

using namespace std;

class Surf{
public:
  //material
  float _sh, _sd, _sf;

  //deterioration rate //  humidity, amount of dirt, amount of fungus
  float _ds, _dp, _df;

  Surf();
  Surf(float sh, float sd, float sf, float ds, float dp, float df);
};

#endif
