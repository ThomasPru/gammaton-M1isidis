#ifndef CVECTOR_HPP_
#define CVECTOR_HPP_

#include <iostream>
#include "Cpoint.hpp"
using namespace std;

class Cvector{
public:
  float x;
  float y;
  float z;
  Cvector();
  Cvector(const Cvector &cv);
  Cvector(Cpoint a, Cpoint b);
  Cvector(double x_c, double y_c, double z_c);

  float getX() const;
  float getY() const;
  float getZ() const;

  void assign( float vx, float vy, float vz );
  void assign( const Cvector &v );

  Cvector operator ^(const Cvector V){
    Cvector Res;
    Res.x = this->y*V.z - this->z*V.y;
    Res.y = this->z*V.x - this->x*V.z;
    Res.z = this->x*V.y - this->y*V.x;
    return Res;
  }

  double operator *(const Cvector V){
    double Res;
    Res += this->x * V.x;
    Res += this->y * V.y;
    Res += this->z * V.z;
    return Res;
  }

};

#endif

